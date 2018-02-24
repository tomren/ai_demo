#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "globals.hpp"
#include "uv.h"
#include "util/sigletion.hpp"

BEGIN_MEATBALL_NAMESPC

class GameLogic : public Singleton<GameLogic>
{
public:
    GameLogic();
    ~GameLogic();

    int32_t Init();
    int32_t Update();

private:
    uv_timer_t mUVTimer;
};

END_MEATBALL_NAMESPC

#endif
