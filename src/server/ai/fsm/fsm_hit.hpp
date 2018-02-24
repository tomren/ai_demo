#ifndef FSM_HIT_H
#define FSM_HIT_H

#include "fsm_base.hpp"

BEGIN_MEATBALL_NAMESPC

class FSMHit : public FSMBase
{
public:
    FSMHit();
    virtual ~FSMHit();

    virtual int32_t Update();
};

END_MEATBALL_NAMESPC

#endif
