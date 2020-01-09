#ifndef GFNET_FNETGT_TCPSERVER_H_
#define GFNET_FNETGT_TCPSERVER_H_

#include "../../../common/common.h"
#include "./Socket.h"
#include "./Acceptor.h"
#include "./EventLoop.h"
#include "./TcpConnection.h"
#include "./fnetgt.h"
#include "./EventLoopThreadPool.h"
#include "../../../base/Log/inc/Logger.h"

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
    // typedef std::function<void(Buffer*)> _func;
    // typedef std::function<void()> Functor;
    TcpServer(const char* __ip, int __port, int __n);
    void Start();
    void SetNewCollectionCallback(NewConnnectionCallback _c);
    void SetMessageCallback(MessageCallback _m);
    void HandleNewConnection(int _f);
    void RemoveConection(const TcpConnectionPtr& _p);

private:
    NewConnnectionCallback newcon_;
    MessageCallback   msgcallback_;
    EventLoop* loop_;
    Acceptor acceptor_;
    std::list<TcpConnectionPtr>        cons_;
    EventLoopThreadPool     pool_;
    uint32_t    poolNums_;
    int connections_;
};

} // namespace Fnetgt

} // namespace gNet


#endif // GFNET_FNETGT_TCPSERVER_H_
