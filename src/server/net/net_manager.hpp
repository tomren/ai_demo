#ifndef NET_MANAGER_H
#define NET_MANAGER_H

#include "globals.hpp"
#include "uv.h"
#include "util/sigletion.hpp"
#include <string>
#include <map>

BEGIN_MEATBALL_NAMESPC

class NetClient;
class NetServer;
class NetConnect;

// ==============================
// 网络地址结构
// ==============================
typedef union
{
    struct sockaddr     addr;
    struct sockaddr_in  addr4;
    struct sockaddr_in6 addr6;
} NetAddr;

// ==============================
// 网络客户端
// ==============================
class NetClient;

// ==============================
// 网络管理
// ==============================
class NetManager : public Singleton<NetManager>
{
public:
    NetManager();
    ~NetManager();

    int32_t Listen(const char* ip, uint32_t port);
    int32_t Update();

    static void OnBind(uv_getaddrinfo_t* req, int status, struct addrinfo* addrs);
    static void OnConn(uv_stream_t* server, int status);
    static void OnDisConnect(NetConnect* netConn);

private:
    static uint64_t GenNetID();
    static NetClient* AddClient();

    static std::string         mIP;
    static uint32_t            mPort;
    static NetServer*          mServers;
    // --------------------------------------------------
    static uv_tcp_t            mTCPHandle;
    static uv_getaddrinfo_t    mUVAddrInfo;
    static struct addrinfo     mAddrInfo;
    // --------------------------------------------------
    static std::map<uint64_t, NetConnect*>  mNetMap;
};


END_MEATBALL_NAMESPC

#endif
