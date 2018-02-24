#ifndef BT_BASE_H
#define BT_BASE_H

#include "ai/ai_base.hpp"

BEGIN_MEATBALL_NAMESPC

class BTBase : public AIBase
{
public:
    BTBase() { }
    virtual ~BTBase() { }

    virtual int32_t Update() = 0;
};

END_MEATBALL_NAMESPC

#endif
