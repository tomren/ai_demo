#ifndef FSM_IDLE_H
#define FSM_IDLE_H

#include "fsm_base.hpp"

BEGIN_MEATBALL_NAMESPC

class FSMIdle : public FSMBase
{
public:
    FSMIdle();
    virtual ~FSMIdle();

    virtual int32_t Update();
};

END_MEATBALL_NAMESPC

#endif
