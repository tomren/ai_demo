#ifndef FSM_CONTROLLER_H
#define FSM_CONTROLLER_H

#include "ai/ai_controller.hpp"

BEGIN_MEATBALL_NAMESPC

class FSMController : public AIController
{
public:
    FSMController();
    virtual ~FSMController();

    virtual int32_t Update();
};

END_MEATBALL_NAMESPC

#endif
