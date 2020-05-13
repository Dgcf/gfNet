#ifndef GFNET_FNETGET_TCPCONNECTION_H_
#define GFNET_FNETGET_TCPCONNECTION_H_

#include "../../../common/common.h"
#include "./Socket.h"
#include "./Channel.h"
#include "./Buffer.h"
#include "./fnetgt.h"
#include "../../../base/Log/inc/Logger.h"

namespace gNet
{

namespace Fnetgt
{

class EventLoop;
class Channel;
/**************************************************************
 * 考虑断线重新连接的情况
 * ************************************************************/
class TcpConnection: public std::enable_shared_from_this<TcpConnection>
{
public:
    NO_COPY(TcpConnection)
    TcpConnection(int _fd, EventLoop* __p);
    
    void ConnectEstablished();
    void ConnectDestroy();

    void Send(const char* _m, int _l);
    
    void HandleRead();
    void HandleWrite();
    void HandleClose();
    void HandleError();

    void SetMessageCallback(MessageCallback __m) { messageCallback_ = __m; }
    void SetCloseCallback(CloseCallback _f) { closeCallback_ = _f; } 

private:
    EventLoop* _lp;
    std::unique_ptr<Channel> chan_;
    Buffer inputBuf_;                                           // fnetgt写入数据，用户从中读数据
    Buffer outputBuf_;                                        // 用户写入数据，gNetgt从中发送数据
    MessageCallback   messageCallback_;
    CloseCallback         closeCallback_;
    Socket  socket_;
};

} // namespace Fnetgt

} // namespace gNet

#endif
