#ifndef GAMESVR_H
#define GAMESVR_H

#include "globals.hpp"
#include "uv.h"

BEGIN_MEATBALL_NAMESPC

class GameServer
{
public:
    GameServer();
    ~GameServer();

    int32_t Init();
    static void Update(uv_timer_t* handle);

    static uv_loop_t* GetUVLoop() { return mUVLoop; }

private:
    static uv_loop_t*       mUVLoop;
    uv_timer_t              mUVTimer;
};

END_MEATBALL_NAMESPC

#endif
