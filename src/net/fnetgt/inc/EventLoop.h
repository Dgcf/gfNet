#ifndef GFNET_FNETGT_EVENTLOOP_H_
#define GFNET_FNETGT_EVENTLOOP_H_

#include "../../../common/common.h"
#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/Channel.h"
#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/IOmultiplexing.h"
#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/Epoll.h"
#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/TcpConnection.h"

namespace gNet
{

namespace Fnetgt
{

class EPoll;
/***********************************************************************
 * 负责IO，调度事件分发
 * 一个EventLoop对象管理若干TcpConnection(Channel)
 * 一条线程只有一个EventLoop
 * *********************************************************************/
class EventLoop
{
public:
    NO_COPY(EventLoop)
    //typedef std::vector<std::unique_ptr<Channel>> ChannelList;
    typedef std::vector<Channel*> ChannelList;
    typedef std::vector<Channel*>::iterator ChannelIter;
    EventLoop();

    void Loop();
    void HandleEvent();
    void Update(uint32_t __e, uint32_t __t, void* _args);

private:
    bool IsLooping_;
    ChannelList channels_;
    std::unique_ptr<EPoll> io_;
};

} // namespace Fnetgt

} // namespace gNet

#endif