#include "../inc/EventLoopThread.h"

namespace gNet
{

namespace Fnetgt
{

EventLoopThread::EventLoopThread():
loop_(NULL),
t_(std::bind(&EventLoopThread::ThreadFunc, this), nullptr)
{

}

EventLoopThread::~EventLoopThread()
{
    t_.join();
}

EventLoop* EventLoopThread::StartLoop()
{
    EventLoop* loop = nullptr;
    
    t_.start();
    if (!loop)
    {
        lock_.Lock();           //  非多线程有必要在这里加锁吗？
        cond_.wait(lock_);
    }
    
    loop = loop_;
    return loop;
}

void* EventLoopThread::ThreadFunc()
{
    EventLoop loop;
    loop_ = &loop;
    cond_.Notify_One();
    loop_->Loop();
}

} // namespace Fnetgt

} // namespace gNet
