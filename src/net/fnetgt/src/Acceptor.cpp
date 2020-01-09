#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/Acceptor.h"

namespace gNet
{

namespace Fnetgt
{

Acceptor::Acceptor(const char* __ip, int __port, EventLoop* __l):
server_socket_(__ip, __port),
channel_(new Channel(server_socket_.Getfd(), __l))
{
    // 在构造函数中做这些操作有什么风险吗？
    server_socket_.Bind();
    server_socket_.Listen();
    // 
    channel_->SetReadCallback(std::bind(&Acceptor::HandleRead, this));
    channel_->EnableReading();
}

void Acceptor::HandleRead()
{
    int clnt_fd = server_socket_.Accept();
    assert(clnt_fd != 0);
    printf("accept success, client fd is: %d\n", clnt_fd);
    if (clnt_fd)
    {
        if (NewConnection_)
        {
            NewConnection_(clnt_fd);   
        }
    }
    else
    {
        // TODO
    }

}

} // namespace Fnetgt

} // namespace gNet
