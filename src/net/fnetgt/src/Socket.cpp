#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/Socket.h"

namespace gNet
{

namespace Fnetgt
{
    
Socket::Socket(const char* __ip, int __port):
ip_(__ip),
port_(__port)
{
    memset(&addr_, 0, sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_addr.s_addr = htonl(INADDR_ANY);      // inet_addr(ip_.c_str());
    addr_.sin_port = htons(port_);
    printf("Port is: %d\n",  port_);
    fd_ = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);   //这里失败怎么搞
    assert(fd_ != 0);
    printf("Create socket success, fd_ is %d\n", fd_);
}

Socket::Socket(int _f):
fd_(_f)
{

}

void Socket::Bind()
{
    GF_CHECK(bind(fd_, (sockaddr*)&addr_, sizeof(addr_)))
    printf("Bind success\n");
}

void Socket::Listen()
{
    GF_CHECK(listen(fd_, 1024))
    printf("Listen success\n");
}

int Socket::Accept()
{
    memset(&clntaddr_, 0, sizeof(clntaddr_));                   // 这里要做修改
    int len = sizeof(clntaddr_);
    return accept(fd_, (sockaddr*)&clntaddr_, (socklen_t*)&len);
}

int Socket::Write(const char* _m, int len)
{
    return write(fd_, _m, len);
}

void Socket::Close()
{
    // 是否使用shutdown？
    GF_CHECK(shutdown(fd_, SHUT_RDWR))
}

} // namespace Fnetgt

} // namespace gNet
