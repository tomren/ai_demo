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
    struct sockaddr_in  addr4;
    struct sockaddr     addr;
    const void          *addrv;
    int32_t             num = 0;
    int32_t             err = 0;

    printf("OnBind\n");

    if (status < 0)
    {
        printf("getaddrinfo(\"%s\"): %s", "192.168.122.1", uv_strerror(status));
        uv_freeaddrinfo(addrs);
        return;
    }

    printf("run bind list\n");

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

        addr4 = *(const struct sockaddr_in *) ai->ai_addr;
        addr4.sin_port = htons(mPort);
        addrv = &addr4.sin_addr;

        uv_inet_ntop(addr.sa_family, addrv, addrbuf, sizeof(addrbuf));
        err = uv_tcp_init(mUVLoop, &mTCPHandle);
        if (0 == err)
        {
            err = uv_listen((uv_stream_t*)&mTCPHandle, 128, OnConn);
        }

        if (0 != err)
        {
            printf("(\"%s:%hu\"): %s", addrbuf, mPort, uv_strerror(err));

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

    printf("OnConn %d", status);

    sx = GET_FIELD(server, ServerCtx, tcp_handle);
    cx = (ClientCtx*)malloc(sizeof(*cx));

    err = uv_tcp_init(mUVLoop, &cx->incoming.handle.tcp);
    printf("uv_tcp_init: %d", err);

    err = uv_accept(server, &cx->incoming.handle.stream);
    printf("uv_accept: %d", err);

    //client_finish_init(sx, cx);
}

END_MEATBALL_NAMESPC