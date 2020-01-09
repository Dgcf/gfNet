#ifndef GFNET_FNETGT_FNETGT_H_
#define GFNET_FNETGT_FNETGT_H_

#include "../../../common/common.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/uio.h>
#include <unistd.h>
#include "../../../base/Log/inc/Logger.h"

namespace gNet
{

namespace Fnetgt
{

class Socket
{
public:
    NO_COPY(Socket)

    Socket(const char* __ip, int __port);
    explicit Socket(int _f);
    void Bind();
    void Listen();
    int Accept();
    int Write(const char* _m, int len);
    void Close();
    int Getfd() const { return fd_; }

private:
    int fd_;
    int port_;
    string ip_;
    struct sockaddr_in addr_;
    struct sockaddr_in clntaddr_;
};

} // namespace Fnetgt

} // namespace gNet

#endif
