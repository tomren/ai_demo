#ifndef BT_CONTROLLER_H
#define BT_CONTROLLER_H

#include "ai/ai_controller.hpp"

BEGIN_MEATBALL_NAMESPC

class BTController : public AIController
{
public:
    BTController();
    virtual ~BTController();

    virtual int32_t Update();
};

END_MEATBALL_NAMESPC

#endif
