#ifndef GFNET_FNETGT_TCPSERVER_H_
#define GFNET_FNETGT_TCPSERVER_H_

#include "../../../common/common.h"
#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/Acceptor.h"
#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/Socket.h"
#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/EventLoop.h"
#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/TcpConnection.h"
#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/fnetgt.h"

using std::placeholders::_1;
using std::placeholders::_2;

namespace gNet
{

namespace Fnetgt
{

class TcpServer
{
public:
    NO_COPY(TcpServer)
    typedef std::shared_ptr<TcpConnection> Tpc;                     // 这里为什么要用shared_ptr，能不能用unique_ptr？
    // typedef std::function<void(Buffer*)> _func;
    // typedef std::function<void()> Functor;
    TcpServer(const char* __ip, int __port);
    void Start();
    void SetNewCollectionCallback(NewConnnectionCallback _c);
    void SetMessageCallback(MessageCallback _m);
    void HandleNewConnection(int _f);

private:
    NewConnnectionCallback newcon_;
    MessageCallback   msgcallback_;
    std::shared_ptr<EventLoop> loop_;
    Acceptor acceptor_;
    std::vector<Tpc>        cons_;
};

} // namespace Fnetgt

} // namespace gNet


#endif // GFNET_FNETGT_TCPSERVER_H_
