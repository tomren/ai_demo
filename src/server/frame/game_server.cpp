#include "game_server.hpp"
#include "net/net_manager.hpp"
#include "game_logic.hpp"

BEGIN_MEATBALL_NAMESPC

// ==============================
// 
// ==============================
uv_loop_t* GameServer::mUVLoop;

// ==============================
// 构造函数
// ==============================
GameServer::GameServer()
{

}

// ==============================
// 析构函数
// ==============================
GameServer::~GameServer()
{

}

// ==============================
// 初始化
// ==============================
int32_t GameServer::Init()
{
    printf("enter Init()\n");

    NetManager::CreateInstance();
    GameLogic::CreateInstance();

    mUVLoop = uv_default_loop();

    uv_timer_init(mUVLoop, &mUVTimer);
    uv_timer_start(&mUVTimer, Update, 0, 100);

    int32_t ret = NetManager::Instance()->Listen("0.0.0.0", 60000);
    if (0 != ret)
    {
        printf("getaddrinfo: '%s'", uv_strerror(ret));
    }

    uv_loop_delete(mUVLoop);
    mUVLoop = NULL;

    return ret;
}

// ==============================
//
// ==============================
void GameServer::Update(uv_timer_t* handle)
{
    NetManager::Instance()->Update();
    GameLogic::Instance()->Update();
}

END_MEATBALL_NAMESPC
