#ifndef NET_CONNECTION_H
#define NET_CONNECTION_H

#include "globals.hpp"
#include "uv.h"
#include <string>

BEGIN_MEATBALL_NAMESPC

// ==============================
// ������
// ==============================
typedef union
{
    uv_handle_t handle;
    uv_stream_t stream;
    uv_tcp_t    tcp;
    uv_udp_t    udp;
} NetHandle;

// ==============================
// ��������
// ==============================
class NetConnect
{
public:
    NetConnect();
    virtual ~NetConnect();

    // ������ջ�����
    static void AllocRecvBuf(uv_handle_t* handle, size_t size, uv_buf_t* buf);

    // ��ȡ������
    static void OnRecvBuf(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf);

    // ���ͻ�����
    static void OnSendBuf(uv_write_t *req, int status);

    // �Ͽ�����
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
