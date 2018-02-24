#include "net_connect.hpp"
#include "net_manager.hpp"
#include <memory.h>

BEGIN_MEATBALL_NAMESPC

// ==============================
// ���캯��
// ==============================
NetConnect::NetConnect()
{

}

// ==============================
// ��������
// ==============================
NetConnect::~NetConnect()
{

}

// ==============================
// ��ȡ���亯��
// ==============================
void NetConnect::AllocRecvBuf(uv_handle_t* handle, size_t size, uv_buf_t* buf)
{
    NetConnect *netConn = GET_FIELD(handle, NetConnect, mNetHandle);
    //ASSERT(c->rdstate == c_busy);
    buf->base = netConn->mRecvBuf;
    buf->len = sizeof(netConn->mRecvBuf);
}

// ==============================
// ��ȡ���ջ�����
// ==============================
void NetConnect::OnRecvBuf(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf)
{
    NetConnect* netConn = GET_FIELD(handle, NetConnect, mNetHandle);
    //ASSERT(c->t.buf == buf->base);
    //ASSERT(c->rdstate == c_busy);
    //c->rdstate = c_done;
    //c->result = nread;

    //uv_read_stop(&netConn->mNetHandle.stream);

    if (UV__EOF == nread)
    {
        NetManager::OnDisConnect(netConn);
        return;
    }

    if (0 == nread)
    {
        printf("net closed\n");
    }

    if (nread > 0)
    {
        netConn->mRecvBuf[nread] = '\0';
        printf("read: %s\n", netConn->mRecvBuf);
        memcpy(netConn->mSendBuf, netConn->mRecvBuf, nread);
    }

    uv_buf_t uvBuf;
    uvBuf.base = netConn->mSendBuf;
    uvBuf.len = nread;
    uv_write(&netConn->mWriteReq, &netConn->mNetHandle.stream, &uvBuf, 1, OnSendBuf);
}

// ==============================
// ���ͻ�����
// ==============================
void NetConnect::OnSendBuf(uv_write_t *req, int status)
{
    NetConnect* netConn = GET_FIELD(req, NetConnect, mWriteReq);

    if (UV_ECANCELED  == status)
    {
        return;  /* Handle has been closed. */
    }
}

// ==============================
// �Ͽ�����
// ==============================
void NetConnect::OnDisconnect()
{

}

END_MEATBALL_NAMESPC
