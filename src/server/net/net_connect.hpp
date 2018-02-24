#ifndef NET_CONNECTION_H
#define NET_CONNECTION_H

#include "globals.hpp"
#include "uv.h"
#include <string>

BEGIN_MEATBALL_NAMESPC

// ==============================
// 网络句柄
// ==============================
typedef union
{
    uv_handle_t handle;
    uv_stream_t stream;
    uv_tcp_t    tcp;
    uv_udp_t    udp;
} NetHandle;

// ==============================
// 网络连接
// ==============================
class NetConnect
{
public:
    NetConnect();
    virtual ~NetConnect();

    // 分配接收缓冲区
    static void AllocRecvBuf(uv_handle_t* handle, size_t size, uv_buf_t* buf);

    // 读取缓冲区
    static void OnRecvBuf(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf);

    // 发送缓冲区
    static void OnSendBuf(uv_write_t *req, int status);

    // 断开连接
    void OnDisconnect();

    uint64_t        mNetID;
    uv_write_t      mWriteReq;
    NetHandle       mNetHandle;
    uv_timer_t      mTimerHandle;
    char            mRecvBuf[1024];
    char            mSendBuf[1024];
};

END_MEATBALL_NAMESPC

#endif
