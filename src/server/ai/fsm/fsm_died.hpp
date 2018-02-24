#ifndef FSM_DIED_H
#define FSM_DIED_H

#include "fsm_base.hpp"

BEGIN_MEATBALL_NAMESPC

class FSMDied : public FSMBase
{
public:
    FSMDied();
    virtual ~FSMDied();

    virtual int32_t Update();
};

END_MEATBALL_NAMESPC

#endif
