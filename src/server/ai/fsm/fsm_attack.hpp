#ifndef FSM_ATTACK_H
#define FSM_ATTACK_H

#include "fsm_base.hpp"

BEGIN_MEATBALL_NAMESPC

class FSMAttack : public FSMBase
{
public:
    FSMAttack();
    virtual ~FSMAttack();

    virtual int32_t Update();
};

END_MEATBALL_NAMESPC

#endif
