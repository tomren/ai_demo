#ifndef GAMESVR_H
#define GAMESVR_H

#include "globals.hpp"
#include "net_manager.hpp"

BEGIN_MEATBALL_NAMESPC

class GameServer
{
public:
    GameServer();
    ~GameServer();

    int32_t Init();
    int32_t Run();

private:
    NetManager mNetMgr;
};

END_MEATBALL_NAMESPC

#endif
