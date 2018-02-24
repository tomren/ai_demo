#ifndef AI_BASE_H
#define AI_BASE_H

#include "globals.hpp"

BEGIN_MEATBALL_NAMESPC

class AIBase
{
public:
    AIBase() { }
    virtual ~AIBase() { }

    virtual int32_t Update() = 0;
};

END_MEATBALL_NAMESPC

#endif