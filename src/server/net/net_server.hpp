#ifndef NET_SERVER_H
#define NET_SERVER_H

#include "globals.hpp"
#include "uv.h"
#include <string>
#include "net_connect.hpp"

BEGIN_MEATBALL_NAMESPC

class NetServer : public NetConnect
{
public:
    NetServer();
    virtual ~NetServer();

    int32_t Update();

private:
    
};

END_MEATBALL_NAMESPC

#endif
