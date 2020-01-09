#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/TcpServer.h"

namespace gNet
{

namespace Fnetgt
{

TcpServer::TcpServer(const char* __ip, int __port, int __n):
loop_(new EventLoop),
acceptor_(__ip, __port, loop_),
poolNums_(__n),
connections_(0)
{
    acceptor_.SetNewConnection(std::bind(&TcpServer::HandleNewConnection, this, _1));
}

void TcpServer::Start()
{
    // Log模块的bug，不析构不会存到文件中去
    LOG_FATAL<< "good";
    for (size_t i = 0; i < poolNums_; i++)
    {
        pool_.Start();
    }
    
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
    ++connections_;
    printf("Create new Connection: %d, Current thread is: %s\n", connections_, CurrentThread::ICurrentthreadID().c_str());

    EventLoop* _lp = pool_.GetNextLoop();
    if (!_lp)
    {
        _lp = loop_;
    }
    
    TcpConnectionPtr _c(new TcpConnection(_f, _lp));
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
    _c->SetCloseCallback(std::bind(&TcpServer::RemoveConection, this, _1));
    // 建立连接之后读事件使能
    _c->ConnectEstablished();
}

void TcpServer::RemoveConection(const TcpConnectionPtr& _p)
{
    printf("Remove Collection\n");
    for (std::list<TcpConnectionPtr>::iterator iter = cons_.begin(); iter != cons_.end(); ++iter)
    {
        if (*iter == _p)
        {
            cons_.remove(*iter);
        }
    }
}


} // namespace Fnetgt

} // namespace gNet
