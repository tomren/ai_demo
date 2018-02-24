#ifndef MONSTER_H
#define MONSTER_H

#include "globals.hpp"
#include "creature.hpp"

BEGIN_MEATBALL_NAMESPC

class Monster : public Creature
{
public:
    Monster();
    virtual ~Monster();

    virtual int32_t Update();
};

END_MEATBALL_NAMESPC

#endif
