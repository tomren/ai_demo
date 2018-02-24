#ifndef CREATURE_H
#define CREATURE_H

#include "globals.hpp"

BEGIN_MEATBALL_NAMESPC

class AIController;

class Creature
{
public:
    Creature() { }
    virtual ~Creature() { }

    virtual int32_t Update() = 0;
private:
    AIController* aiCont;
};

END_MEATBALL_NAMESPC

#endif