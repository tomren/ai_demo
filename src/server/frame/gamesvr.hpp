#ifndef GAMESVR_H
#define GAMESVR_H

#include "globals.hpp"
#include "netmgr.hpp"

BEGIN_NAMESPACE

class GameServer
{
public:
    GameServer();
    ~GameServer();

    int32_t Init();
    int32_t Run();

private:
    NetMgr mNetMgr;
};

END_NAMESPACE

#endif