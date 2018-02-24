#ifndef AI_CONTROLLER_H
#define AI_CONTROLLER_H

#include "globals.hpp"

BEGIN_MEATBALL_NAMESPC

class AIController
{
public:
    AIController() { }
    virtual ~AIController() { }

    virtual int32_t Update() = 0;
};

END_MEATBALL_NAMESPC

#endif