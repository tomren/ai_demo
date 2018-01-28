#include "netmgr.hpp"
#include <memory.h>

BEGIN_MEATBALL_NAMESPC

std::string         NetMgr::mIP;
uint32_t            NetMgr::mPort;
uv_loop_t*          NetMgr::mUVLoop;
ServerCtx*          NetMgr::mServers;
// --------------------------------------------------
uv_tcp_t            NetMgr::mTCPHandle;
uv_getaddrinfo_t    NetMgr::mUVAddrInfo;
struct addrinfo     NetMgr::mAddrInfo;



// ==============================
//
// ==============================
NetMgr::NetMgr()
{

}

// ==============================
//
// ==============================
NetMgr::~NetMgr()
{

}

// ==============================
//
// ==============================
int32_t NetMgr::Listen(const char* ip, uint32_t port)
{
    struct addrinfo hints;
    int32_t err = 0;

    mIP     = ip;
    mPort   = port;
    mUVLoop = uv_default_loop();

    memset(&hints, 0, sizeof(hints));
    hints.ai_family     = AF_UNSPEC;
    hints.ai_socktype   = SOCK_STREAM;
    hints.ai_protocol   = IPPROTO_TCP;

    printf("begin uv_getaddrinfon\n");
    err = uv_getaddrinfo(mUVLoop, &mUVAddrInfo, OnBind, ip, NULL, &hints);
    if (0 != err)
    {
        printf("getaddrinfo: '%s'\n", uv_strerror(err));
        return err;
    }
    printf("end uv_getaddrinfon\n");

    printf("begin uv_run\n");
    if (uv_run(mUVLoop, UV_RUN_DEFAULT))
    {
        //abort();
    }
    printf("end uv_run\n");

    printf("hahahaha\n");

    uv_loop_delete(mUVLoop);
    mUVLoop = NULL;
    return err;
}

// ==============================
//
// ==============================
int32_t NetMgr::Update()
{
    return 0;
}

// ==============================
//
// ==============================
void NetMgr::OnBind(uv_getaddrinfo_t *req, int status, struct addrinfo *addrs)
{
    char                addrbuf[64];
    unsigned int        ipv4_naddrs = 0;
    NetAddr             netAddr;
    int32_t             num = 0;
    int32_t             err = 0;

    if (status < 0)
    {
        printf("getaddrinfo(\"%s\"): %s", mIP.c_str(), uv_strerror(status));
        uv_freeaddrinfo(addrs);
        return;
    }

    for (struct addrinfo* ai = addrs; ai != NULL; ai = ai->ai_next)
    {
        if (ai->ai_family == AF_INET)
        {
            ++ipv4_naddrs;
        }
    }

    printf("malloc server list\n");

    mServers = (ServerCtx*)malloc(ipv4_naddrs * sizeof(mServers[0]));

    printf("begin addr\n");

    for (struct addrinfo* ai = addrs; ai != NULL; ai = ai->ai_next)
    {
        if (ai->ai_family != AF_INET)
            continue;

        netAddr.addr4 = *(const struct sockaddr_in *) ai->ai_addr;
        netAddr.addr4.sin_port = htons(mPort);

        uv_inet_ntop(netAddr.addr.sa_family, &netAddr.addr4, addrbuf, sizeof(addrbuf));

        err = uv_tcp_init(mUVLoop, &mServers[num].tcp_handle);

        err = uv_tcp_bind(&mServers[num].tcp_handle, &netAddr.addr, 0);
        std::string errStr = uv_strerror(err);

        if (0 == err)
        {
            err = uv_listen((uv_stream_t*)&mServers[num].tcp_handle, 128, OnConn);
        }

        if (0 != err)
        {
            printf("(\"%s:%hu\"): %s", addrbuf, mPort, uv_strerror(err));
            exit(0);
            break;

            while (num > 0)
            {
                --num;
                uv_close((uv_handle_t *) (mServers + num), NULL);
            }
        }

        printf("listening on %s:%hu\n", addrbuf, mPort);

        ++num;
    }

    printf("end addr\n");

    uv_freeaddrinfo(addrs);
}

void NetMgr::OnConn(uv_stream_t* server, int status)
{
    int32_t     err = 0;
    ServerCtx*  sx = NULL;
    ClientCtx*  cx = NULL;

    printf("OnConn %d\n", status);

    sx = GET_FIELD(server, ServerCtx, tcp_handle);
    cx = (ClientCtx*)malloc(sizeof(*cx));

    err = uv_tcp_init(mUVLoop, &cx->incoming.handle.tcp);
    printf("uv_tcp_init: %d\n", err);

    err = uv_accept(server, &cx->incoming.handle.stream);
    printf("uv_accept: %d\n", err);

    ClientFinishInit(sx, cx);
}

void NetMgr::ClientFinishInit(ServerCtx *sx, ClientCtx *cx)
{
    NetConn *incoming;
    NetConn *outgoing;

    cx->sx = sx;
    //s5_init(&cx->parser);

    incoming = &cx->incoming;
    incoming->client = cx;
    incoming->result = 0;
    incoming->rdstate = c_stop;
    incoming->wrstate = c_stop;
    //incoming->idle_timeout = sx->idle_timeout;
    uv_timer_init(mUVLoop, &incoming->timer_handle);

    outgoing = &cx->outgoing;
    outgoing->client = cx;
    outgoing->result = 0;
    outgoing->rdstate = c_stop;
    outgoing->wrstate = c_stop;
    //outgoing->idle_timeout = sx->idle_timeout;
    uv_tcp_init(mUVLoop, &outgoing->handle.tcp);
    uv_timer_init(mUVLoop, &outgoing->timer_handle);

    // Wait for the initial packet
    ConnRead(incoming);
}

void NetMgr::ConnRead(NetConn* c)
{
    uv_read_start(&c->handle.stream, ConnAlloc, ConnReadDone);
    c->rdstate = c_busy;
}

void NetMgr::ConnTimerReset(NetConn* c)
{
    //uv_timer_start(&c->timer_handle, conn_timer_expire, c->idle_timeout, 0);
}

void NetMgr::ConnAlloc(uv_handle_t* handle, size_t size, uv_buf_t* buf)
{
    NetConn *c = NULL;

    c = GET_FIELD(handle, NetConn, handle);
    //ASSERT(c->rdstate == c_busy);
    buf->base = c->t.buf;
    buf->len = sizeof(c->t.buf);
}

void NetMgr::ConnReadDone(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf)
{
    NetConn *c = NULL;

    c = GET_FIELD(handle, NetConn, handle);
    //ASSERT(c->t.buf == buf->base);
    //ASSERT(c->rdstate == c_busy);
    c->rdstate = c_done;
    c->result = nread;

    uv_read_stop(&c->handle.stream);

    if (0 == nread)
    {
        printf("net closed\n");
    }

    if (nread > 0)
    {
        c->t.buf[nread] = '\0';
        printf("read: %s\n", c->t.buf);
    }

    //do_next(c->client);
    ConnRead(c);
}

END_MEATBALL_NAMESPC
