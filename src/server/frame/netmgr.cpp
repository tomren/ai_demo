#include "netmgr.hpp"

BEGIN_NAMESPACE

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
int32_t NetMgr::Init(const char* ip, uint32_t port)
{
    mUVLoop = uv_default_loop();

    uv_getaddrinfo(mUVLoop, &mUVAddrInfo, OnBind, ip, NULL, &mAddrInfo);

    if (uv_run(mUVLoop, UV_RUN_DEFAULT)) {
        //abort();

    }

    return 0;
}

// ==============================
//
// ==============================
int32_t NetMgr::Listen(const char* ip, uint32_t port)
{
    return 0;
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
    if (status < 0)
    {
        printf("getaddrinfo(\"%s\"): %s", "0.0.0.0", uv_strerror(status));
        uv_freeaddrinfo(addrs);
        return;
    }
}

END_NAMESPACE