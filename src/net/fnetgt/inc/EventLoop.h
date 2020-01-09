#ifndef GFNET_FNETGT_EVENTLOOP_H_
#define GFNET_FNETGT_EVENTLOOP_H_

#include "../../../common/common.h"
#include "./Channel.h"
#include "./IOmultiplexing.h"
#include "./Epoll.h"
#include "./TcpConnection.h"
#include "../../../base/Log/inc/Logger.h"

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
    void RemoveChannel(Channel* _r);

private:
    bool IsLooping_;
    ChannelList channels_;
    std::unique_ptr<EPoll> io_;
};

} // namespace Fnetgt

} // namespace gNet

#endif