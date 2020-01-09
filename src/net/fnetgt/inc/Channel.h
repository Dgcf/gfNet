#ifndef GFNET_FNETGT_CHANNEL_H_
#define GFNET_FNETGT_CHANNEL_H_

#include "../../../common/common.h"
#include <sys/epoll.h>
#include "./EventLoop.h"
#include "../../../base/Log/inc/Logger.h"

namespace gNet
{
    
namespace Fnetgt
{

enum ctl_state
{
    ctl_state_Add = 0,
    ctl_state_Mod = 1,
    ctl_state_Del = 2
};

class EventLoop;
class Channel
{
public:
    //NO_COPY(Channel)
    typedef std::function<void()> Functor;
    Channel(int _f, EventLoop* _l);

    void EnableReading() { events_ |= EPOLLIN; Update();}
    void DisableReading() { events_ &= ~ EPOLLIN;  Update(); }
    void EnableWriting() { events_ |= EPOLLOUT; Update(); }
    void DisableWriting() { events_ &= ~EPOLLOUT; Update(); }
    void EnableError() { events_ |= EPOLLERR; Update(); }
    void DisableError() { events_ &= ~EPOLLERR; Update(); }
    void EnableClose() { events_ |= EPOLLRDHUP; Update(); }
    void DisableClose() { events_ &= ~EPOLLRDHUP; Update(); }
    void DisableAll() { events_ = 0; Update(); }

    void SetReadCallback(Functor _r) { readCallback_ = _r; }
    void SetWriteCallback(Functor _w) { writeCallback_ = _w; }
    void SetCloseCallback(Functor _c) { closeCallback_ = _c; }
    void SetErrorCallback(Functor _e) { errorCallback_ = _e; }

    void Update();
    void ResetCurEvent(uint32_t __e) { curevents_ = __e; }
    void HandleEvent();
    int GetFd() const { return fd_; }
    int GetEventsState() const { return events_; }
    void SetIndex(ctl_state _d) { index_ = _d; }
    ctl_state GetIndex() const { return index_; }
    void RemoveFromLoop();

private:
    int fd_;
    ctl_state index_;
    uint32_t events_;                       // 设置下去的epoll事件
    uint32_t  curevents_;               // 当前监视的事件类型
    EventLoop* lp_;
    Functor     readCallback_;
    Functor     writeCallback_;
    Functor     closeCallback_;
    Functor     errorCallback_;
};

} // namespace Fnetgt

} // namespace gNet

#endif
