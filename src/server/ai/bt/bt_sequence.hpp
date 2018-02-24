#ifndef BT_SEQUENCE_H
#define BT_SEQUENCE_H

#include "bt_base.hpp"

BEGIN_MEATBALL_NAMESPC

class BTSequence : public BTBase
{
public:
    BTSequence();
    virtual ~BTSequence();

    virtual int32_t Update();
};

END_MEATBALL_NAMESPC

#endif
