#include "game_server.hpp"

BEGIN_MEATBALL_NAMESPC

// ==============================
// ���캯��
// ==============================
GameServer::GameServer()
{

}

// ==============================
// ��������
// ==============================
GameServer::~GameServer()
{

}


// ==============================
// ��ʼ��
// ==============================
int32_t GameServer::Init()
{
    printf("enter Init()\n");
    int32_t ret = mNetMgr.Listen("0.0.0.0", 60000);
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

END_MEATBALL_NAMESPC
