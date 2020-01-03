#ifndef GFNET_FNETGET_TCPCONNECTION_H_
#define GFNET_FNETGET_TCPCONNECTION_H_

#include "../../../common/common.h"
#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/Socket.h"
#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/Channel.h"
#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/Buffer.h"
#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/fnetgt.h"

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
    TcpConnection(int _fd, std::shared_ptr<EventLoop> __p);
    
    void ConnectEstablished();
    void ConnectDestroy();

    void Send(const char* _m, int _l);
    
    void HandleRead();
    void HandleWrite();
    void HandleClose();
    void HandleError();

    void SetMessageCallback(MessageCallback __m) { messageCallback_ = __m; }
private:
    std::shared_ptr<EventLoop> _lp;
    std::unique_ptr<Channel> chan_;
    Buffer inputBuf_;                                           // fnetgt写入数据，用户从中读数据
    Buffer outputBuf_;                                        // 用户写入数据，gnetgt从中发送数据
    MessageCallback   messageCallback_;
    Socket  socket_;
};

} // namespace Fnetgt

} // namespace gNet

#endif
