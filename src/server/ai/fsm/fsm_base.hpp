#ifndef FSM_BASE_H
#define FSM_BASE_H

#include "ai/ai_base.hpp"

BEGIN_MEATBALL_NAMESPC

class FSMBase : public AIBase
{
public:
    FSMBase() { }
    virtual ~FSMBase() { }

    virtual int32_t Update() = 0;
};

END_MEATBALL_NAMESPC

#endif
