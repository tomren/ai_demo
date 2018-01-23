#include "gamesvr.hpp"

BEGIN_MEATBALL_NAMESPC

// ==============================
//
// ==============================
GameServer::GameServer()
{

}

// ==============================
//
// ==============================
GameServer::~GameServer()
{

}


// ==============================
//
// ==============================
int32_t GameServer::Init()
{
    printf("enter Init()\n");
    int32_t ret = mNetMgr.Listen("0.0.0.0", 8000);
    if (0 != ret)
        return ret;

    printf("what tom\n");

    if (0 != ret)
    {
        printf("getaddrinfo: '%s'", uv_strerror(ret));
        return ret;
    }

    printf("wocao\n");

    return ret;
}

// ==============================
//
// ==============================
int32_t GameServer::Run()
{
    return 0;
}

END_MEATBALL_NAMESPC