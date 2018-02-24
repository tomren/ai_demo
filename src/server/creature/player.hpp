#ifndef PLAYER_H
#define PLAYER_H

#include "globals.hpp"
#include "creature.hpp"

BEGIN_MEATBALL_NAMESPC

class Player : public Creature
{
public:
    Player();
    virtual ~Player();

    virtual int32_t Update();
};

END_MEATBALL_NAMESPC

#endif
