#ifndef FSM_CHASE_H
#define FSM_CHASE_H

#include "fsm_base.hpp"

BEGIN_MEATBALL_NAMESPC

class FSMChase : public FSMBase
{
public:
    FSMChase();
    virtual ~FSMChase();

    virtual int32_t Update();
};

END_MEATBALL_NAMESPC

#endif
