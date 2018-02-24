#ifndef FSM_PATROL_H
#define FSM_PATROL_H

#include "fsm_base.hpp"

BEGIN_MEATBALL_NAMESPC

class FSMPatrol : public FSMBase
{
public:
    FSMPatrol();
    virtual ~FSMPatrol();

    virtual int32_t Update();
};

END_MEATBALL_NAMESPC

#endif
