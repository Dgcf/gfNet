#ifndef GFNET_FNETGT_EPOLL_H_
#define GFNET_FNETGT_EPOLL_H_

#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/IOmultiplexing.h"

namespace gNet
{

namespace Fnetgt
{

class Channel;
// class IOMulti;
/******************************************************
 * 主要负责网络事件的监听
 * ****************************************************/
class EPoll
{
public:
    EPoll();
    void Poller(std::vector<Channel*>* __c);
    void Update(uint32_t __e, uint32_t __t, void* _args);

private:
    int epfd;
    const int size_;
    const int timeout_;
    epoll_event* event_;
    std::vector<Channel*> channels_;
};

} // namespace Fnetgt

} // namespace gNet

#endif