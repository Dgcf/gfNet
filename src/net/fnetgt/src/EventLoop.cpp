#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/EventLoop.h"

namespace gNet
{

namespace Fnetgt
{

EventLoop::EventLoop():
IsLooping_(true),
io_(new EPoll)
{

}

void EventLoop::HandleEvent()
{
    for (ChannelIter iter = channels_.begin(); iter != channels_.end(); ++iter)
    {
        (*iter)->HandleEvent();
    }
}

void EventLoop::Loop()
{
    while (IsLooping_)
    {
        io_->Poller(&channels_);
        for (ChannelIter iter = channels_.begin(); iter != channels_.end(); ++iter)
        {
             (*iter)->HandleEvent();
        }
    }
}

void EventLoop::Update(uint32_t __e, uint32_t __t, void* _args)
{
    io_->Update(__e, __t, _args);
}

void EventLoop::RemoveChannel(Channel* _r)
{
    for (ChannelIter iter = channels_.begin(); iter != channels_.end(); ++iter)
    {
        if (_r == *iter)
        {
            channels_.erase(iter);
            return;
        }
    }
}

} // namespace Fnetgt

} // namespace gNet
