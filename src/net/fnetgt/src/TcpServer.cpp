#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/TcpServer.h"

namespace gNet
{

namespace Fnetgt
{

TcpServer::TcpServer(const char* __ip, int __port):
loop_(new EventLoop),
acceptor_(__ip, __port, loop_)
{
    acceptor_.SetNewConnection(std::bind(&TcpServer::HandleNewConnection, this, _1));
}

void TcpServer::Start()
{
    loop_->Loop();
}

void TcpServer::SetNewCollectionCallback(NewConnnectionCallback _c)
{
    newcon_ = _c;
}

void TcpServer::SetMessageCallback(MessageCallback _m)
{
    msgcallback_ = _m;
}

void TcpServer::HandleNewConnection(int _f)
{
    printf("Create new Connection\n");
    Tpc _c(new TcpConnection(_f, loop_));
    cons_.push_back(_c);
    // 注册回调告诉用户新的连接
    if (newcon_)
    {
        newcon_();
    }
    if (msgcallback_)
    {
        _c->SetMessageCallback(msgcallback_);
    }
    // 建立连接之后读事件使能
    _c->ConnectEstablished();
}


} // namespace Fnetgt

} // namespace gNet
