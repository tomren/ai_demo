#ifndef NETMGR_H
#define NETMGR_H

#include "globals.hpp"
#include "uv.h"
#include <string>

BEGIN_MEATBALL_NAMESPC

struct ClientCtx;

enum ConnState
{
    c_busy,  /* Busy; waiting for incoming data or for a write to complete. */
    c_done,  /* Done; read incoming data or write finished. */
    c_stop,  /* Stopped. */
    c_dead
};

typedef struct NetConn
{
    unsigned char       rdstate;
    unsigned char       wrstate;
    unsigned int        idle_timeout;
    struct ClientCtx*   client;  /* Backlink to owning client context. */
    ssize_t             result;

    union
    {
        uv_handle_t handle;
        uv_stream_t stream;
        uv_tcp_t    tcp;
        uv_udp_t    udp;
    } handle;

    uv_timer_t timer_handle;  /* For detecting timeouts. */
    uv_write_t write_req;

    /* We only need one of these at a time so make them share memory. */
    union
    {
        uv_getaddrinfo_t    addrinfo_req;
        uv_connect_t        connect_req;
        uv_req_t            req;
        struct sockaddr_in6 addr6;
        struct sockaddr_in  addr4;
        struct sockaddr     addr;
        char buf[2048];  /* Scratch space. Used to read data into. */
    } t;
} NetConn;

typedef struct NetConfig
{
    std::string ip;
    uint32_t port;
} NetConfig;

typedef struct ServerCtx
{
    uv_tcp_t tcp_handle;
} ServerCtx;

typedef struct ClientCtx
{
    unsigned int state;
    ServerCtx *sx;      /* Backlink to owning server context. */
    NetConn incoming;   /* Connection with the SOCKS client. */
    NetConn outgoing;   /* Connection with upstream. */
} ClientCtx;

typedef struct NetState
{
    uv_getaddrinfo_t getaddrinfo_req;
    ServerCtx *servers;
    uv_loop_t *loop;
} NetState;

// ==============================
// 网络地址结构
// ==============================
typedef union
{
    struct sockaddr     addr;
    struct sockaddr_in  addr4;
    struct sockaddr_in6 addr6;
} NetAddr;

// ==============================
// 网络管理
// ==============================
class NetMgr
{
public:
    NetMgr();
    ~NetMgr();

    int32_t Listen(const char* ip, uint32_t port);
    int32_t Update();

    static void OnBind(uv_getaddrinfo_t* req, int status, struct addrinfo* addrs);
    static void OnConn(uv_stream_t* server, int status);

private:
    static void ClientFinishInit(ServerCtx* sx, ClientCtx* cx);
    static void ConnRead(NetConn* c);
    static void ConnTimerReset(NetConn* c);
    static void ConnAlloc(uv_handle_t* handle, size_t size, uv_buf_t* buf);
    static void ConnReadDone(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf);

    static std::string         mIP;
    static uint32_t            mPort;
    static uv_loop_t*          mUVLoop;
    static ServerCtx*          mServers;
    // --------------------------------------------------
    static uv_tcp_t            mTCPHandle;
    static uv_getaddrinfo_t    mUVAddrInfo;
    static struct addrinfo     mAddrInfo;
};


END_MEATBALL_NAMESPC

#endif