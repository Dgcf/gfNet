#ifndef GFNET_FNETGT_ACCEPTOR_H_
#define GFNET_FNETGT_ACCEPTOR_H_

#include "../../../common/common.h"
#include "./Socket.h"
#include "./Channel.h"
#include "./TcpConnection.h"
#include "./EventLoop.h"
#include "../../../base/Log/inc/Logger.h"

namespace gNet
{

namespace Fnetgt
{

/******************************************************
 * 处理接收新的连接
 * ****************************************************/
class Acceptor
{
public:
    NO_COPY(Acceptor)
    typedef std::function<void(int _f)> Functor;

    Acceptor(const char* __ip, int __port, EventLoop* __l);
    void SetNewConnection(Functor _func) { NewConnection_ = _func; }
    void HandleRead();
    void HandleNewConnection(int _f, std::shared_ptr<EventLoop> _p);

private:
    Socket server_socket_;
    std::unique_ptr<Channel> channel_;
    std::unique_ptr<TcpConnection> newcon_;
    Functor NewConnection_;
};

} // namespace Fnetgt

} // namespace gNet



#endif
