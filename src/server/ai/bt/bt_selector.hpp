#ifndef BT_SELECTOR_H
#define BT_SELECTOR_H

#include "bt_base.hpp"

BEGIN_MEATBALL_NAMESPC

class BTSelector : public BTBase
{
public:
    BTSelector();
    virtual ~BTSelector();

    virtual int32_t Update();
};

END_MEATBALL_NAMESPC

#endif
