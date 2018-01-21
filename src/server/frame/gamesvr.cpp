#include "gamesvr.hpp"

BEGIN_NAMESPACE

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
    int32_t ret = mNetMgr.Init("0.0.0.0", 8000);
    if (0 != ret)
        return ret;

    if (0 != ret)
    {
        printf("getaddrinfo: '%s'", uv_strerror(ret));
        return ret;
    }

    return ret;
}

// ==============================
//
// ==============================
int32_t GameServer::Run()
{
    return 0;
}

END_NAMESPACE