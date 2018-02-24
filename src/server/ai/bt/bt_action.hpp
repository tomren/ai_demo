#ifndef BT_ACTION_H
#define BT_ACTION_H

#include "bt_base.hpp"

BEGIN_MEATBALL_NAMESPC

class BTAction : public BTBase
{
public:
    BTAction();
    virtual ~BTAction();

    virtual int32_t Update();
};

END_MEATBALL_NAMESPC

#endif
