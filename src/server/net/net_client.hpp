#ifndef NET_CLIENT_H
#define NET_CLIENT_H

#include <string>
#include "globals.hpp"
#include "uv.h"
#include "net_connect.hpp"

BEGIN_MEATBALL_NAMESPC

// ==============================
// Õ¯¬Áπ‹¿Ì
// ==============================
class NetClient : public NetConnect
{
public:
    NetClient();
    virtual ~NetClient();
};

END_MEATBALL_NAMESPC

#endif
