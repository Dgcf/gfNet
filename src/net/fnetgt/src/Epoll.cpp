#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/Epoll.h"

namespace gNet
{

namespace Fnetgt
{

EPoll::EPoll():
size_(1024),
timeout_(10000)
{
    event_ = new epoll_event[size_];             // size需要改动
    memset(event_, 0, sizeof(*event_));
    epfd = epoll_create(size_); 
    assert(epfd != -1);
    printf("epoll_create success! \n");
}

void EPoll::Poller(std::vector<Channel*>* __c)
{
    __c->clear();
    int nums = epoll_wait(epfd, event_, size_, timeout_);
    printf("epoll wait: %d\n", nums);
    for (size_t i = 0; i < nums; ++i)
    {
        Channel* _l(static_cast<Channel*>(event_[i].data.ptr));
        _l->ResetCurEvent(event_[i].events);
        __c->push_back(_l);
    }
}

void EPoll::Update(uint32_t __e, uint32_t __t, void* _args)
{
    epoll_event events;
    events.events = __t;
    events.data.fd = __e;
    events.data.ptr = _args;
    printf("epoll_ctl, fd is:%d, event is: %d\n", __e, __t);
    GF_CHECK(epoll_ctl(epfd, EPOLL_CTL_ADD, __e, &events))
}

} // namespace Fnetgt

} // namespace gNet
