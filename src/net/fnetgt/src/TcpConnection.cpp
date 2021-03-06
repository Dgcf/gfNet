#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/TcpConnection.h"

namespace gNet
{

namespace Fnetgt
{

TcpConnection::TcpConnection(int _fd, EventLoop* __p):
chan_(new Channel(_fd, __p)),
socket_(_fd)
{
    chan_->SetReadCallback(std::bind(&TcpConnection::HandleRead, this));
    chan_->SetWriteCallback(std::bind(&TcpConnection::HandleWrite, this));
    chan_->SetCloseCallback(std::bind(&TcpConnection::HandleClose, this));
    chan_->SetErrorCallback(std::bind(&TcpConnection::HandleError, this));
}

void TcpConnection::ConnectEstablished()
{
    // 新的连接建立之后是读
    chan_->SetIndex(ctl_state_Add);
    chan_->EnableReading();
}

void TcpConnection::ConnectDestroy()
{
    chan_->DisableAll();
}

void TcpConnection::Send(const char* _m, int _l)
{
    int len = write(chan_->GetFd(), _m,  _l);
    if (len < _l)
    {
        // 没有发送完的这部分数据放到outbuf_中去发送
        outputBuf_.Append(_m, _l-len);
        //添加到读事件
        chan_->EnableWriting();
    }
}

void TcpConnection::HandleRead()
{
    // EPOLLRDHUP
    const int len = inputBuf_.ReadFd(socket_.Getfd());
    if (len > 0)
    {
        messageCallback_(shared_from_this(), inputBuf_.peek(), inputBuf_.ReadableBytes()); 
        // 更新readndex_
        inputBuf_.CompleteRead();
    }
    else if (len == 0)      // 读到0是否意味着关闭连接？TODO
    {
        HandleClose();
    }
    else if (len < 0)
    {
        HandleError();
    }
}

void TcpConnection::HandleWrite()
{
    int len = socket_.Write(outputBuf_.peek(), outputBuf_.ReadableBytes());
    outputBuf_.CompleteRead();
}

// 断开连接后需要关闭epoll
// 析构TcpConnection和Channel
void TcpConnection::HandleClose()
{
    chan_->DisableAll();
    closeCallback_(shared_from_this());
    chan_->RemoveFromLoop();
    // 最后关闭socket
    socket_.Close();
}

void TcpConnection::HandleError()
{
    // 什么时候出现error，error怎么处理？
}

} // namespace Fnetgt

} // namespace gNet
