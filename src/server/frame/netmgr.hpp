#ifndef NETMGR_H
#define NETMGR_H

#include "globals.hpp"
#include "uv.h"

BEGIN_NAMESPACE

class NetMgr
{
public:
    NetMgr();
    ~NetMgr();

    int32_t Init(const char* ip, uint32_t port);
    int32_t Listen(const char* ip, uint32_t port);
    int32_t Update();

    static void OnBind(uv_getaddrinfo_t *req, int status, struct addrinfo *addrs);

private:
    uv_loop_t*          mUVLoop;
    uv_getaddrinfo_t    mUVAddrInfo;
    struct addrinfo     mAddrInfo;
};


END_NAMESPACE

#endif