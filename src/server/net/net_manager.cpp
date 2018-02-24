#include "net_manager.hpp"
#include "net_client.hpp"
#include "net_server.hpp"
#include "frame/game_server.hpp"
#include <memory.h>

BEGIN_MEATBALL_NAMESPC

std::string         NetManager::mIP;
uint32_t            NetManager::mPort;
NetServer*          NetManager::mServers;
// --------------------------------------------------
uv_tcp_t            NetManager::mTCPHandle;
uv_getaddrinfo_t    NetManager::mUVAddrInfo;
struct addrinfo     NetManager::mAddrInfo;
std::map<uint64_t, NetConnect*>  NetManager::mNetMap;

// ==============================
// 构造函数
// ==============================
NetManager::NetManager()
{

}

// ==============================
// 析构函数
// ==============================
NetManager::~NetManager()
{

}

// ==============================
//
// ==============================
int32_t NetManager::Listen(const char* ip, uint32_t port)
{
    struct addrinfo hints;
    int32_t err = 0;

    mIP     = ip;
    mPort   = port;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family     = AF_UNSPEC;
    hints.ai_socktype   = SOCK_STREAM;
    hints.ai_protocol   = IPPROTO_TCP;

    printf("begin uv_getaddrinfon\n");
    err = uv_getaddrinfo(GameServer::GetUVLoop(), &mUVAddrInfo, OnBind, ip, NULL, &hints);
    if (0 != err)
    {
        printf("getaddrinfo: '%s'\n", uv_strerror(err));
        return err;
    }
    printf("end uv_getaddrinfon\n");

    printf("begin uv_run\n");
    if (uv_run(GameServer::GetUVLoop(), UV_RUN_DEFAULT))
    {
        //abort();
    }
    printf("end uv_run\n");

    printf("hahahaha\n");

    return err;
}

// ==============================
//
// ==============================
int32_t NetManager::Update()
{
    return 0;
}

// ==============================
//
// ==============================
void NetManager::OnBind(uv_getaddrinfo_t *req, int status, struct addrinfo *addrs)
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

    mServers = (NetServer*)malloc(ipv4_naddrs * sizeof(mServers[0]));

    printf("begin addr\n");

    for (struct addrinfo* ai = addrs; ai != NULL; ai = ai->ai_next)
    {
        if (ai->ai_family != AF_INET)
            continue;

        netAddr.addr4 = *(const struct sockaddr_in *) ai->ai_addr;
        netAddr.addr4.sin_port = htons(mPort);

        uv_inet_ntop(netAddr.addr.sa_family, &netAddr.addr4, addrbuf, sizeof(addrbuf));

        err = uv_tcp_init(GameServer::GetUVLoop(), &mServers[num].mNetHandle.tcp);

        err = uv_tcp_bind(&mServers[num].mNetHandle.tcp, &netAddr.addr, 0);
        std::string errStr = uv_strerror(err);

        if (0 == err)
        {
            err = uv_listen((uv_stream_t*)&mServers[num].mNetHandle.tcp, 128, OnConn);
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

void NetManager::OnConn(uv_stream_t* server, int status)
{
    printf("OnConn %d\n", status);

    NetServer* netSvr = GET_FIELD(server, NetServer, mNetHandle);
    NetClient* netCli = AddClient();

    mNetMap[netCli->mNetID] = netCli;

    //err = uv_tcp_init(mUVLoop, &cx->incoming.handle.tcp);
    int32_t err = uv_tcp_init(GameServer::GetUVLoop(), &netCli->mNetHandle.tcp);
    printf("uv_tcp_init: %d\n", err);

    //err = uv_accept(server, &cx->incoming.handle.stream);
    err = uv_accept(server, &netCli->mNetHandle.stream);
    printf("uv_accept: %d\n", err);

    uv_read_start(&netCli->mNetHandle.stream, NetConnect::AllocRecvBuf, NetConnect::OnRecvBuf);
    //ClientFinishInit(sx, cx);

    uv_timer_init(GameServer::GetUVLoop(), &netCli->mTimerHandle);
}

void NetManager::OnDisConnect(NetConnect* netConn)
{
    if (NULL == netConn)
        return;

    netConn->OnDisconnect();

    std::map<uint64_t, NetConnect*>::iterator it = mNetMap.find(netConn->mNetID);
    if (it == mNetMap.end())
    {
        printf("Net Error");
        return;
    }

    mNetMap.erase(it);
}

uint64_t NetManager::GenNetID()
{
    static uint64_t netID = 0;
    return ++netID;
}

NetClient* NetManager::AddClient()
{
    NetClient* client = (NetClient*)malloc(sizeof(NetClient));
    client->mNetID = GenNetID();
    return client;
}

END_MEATBALL_NAMESPC
