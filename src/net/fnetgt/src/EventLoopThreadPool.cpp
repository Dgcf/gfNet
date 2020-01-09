#include "../inc/EventLoopThreadPool.h"

namespace gNet
{

namespace Fnetgt
{
    
EventLoopThreadPool::EventLoopThreadPool():
next_(0)
{
}

EventLoopThreadPool::~EventLoopThreadPool()
{
}

void EventLoopThreadPool::Start()
{
    EventLoopThread* _t = new EventLoopThread;          // TODO 未销毁
    threads_.push_back(_t);
    loops_.push_back(_t->StartLoop());
}

EventLoop* EventLoopThreadPool::GetNextLoop()
{
    if (loops_.size() == 0)
    {
        return nullptr;
    }
    
    if (next_ >= loops_.size())
    {
        next_ = 0;
    }
    return loops_[next_++];
}

} // namespace Fnetgt

} // namespace gNet
