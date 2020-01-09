#ifndef GFNET_FNETGT_EVENTLOOPTHREAD_H_
#define GFNET_FNETGT_EVENTLOOPTHREAD_H_

#include "../../../common/common.h"
#include "./EventLoop.h"
#include "../../../base/Thread/inc/thread.h"
#include "../../../base/Thread/inc/Mutex.h"
#include "../../../base/Thread/inc/Condition.h"

namespace gNet
{

namespace Fnetgt
{

class EventLoopThread
{
public:
    NO_COPY(EventLoopThread)
    EventLoopThread();
    ~EventLoopThread();
    EventLoop* StartLoop();
    void* ThreadFunc();
    
private:
    EventLoop* loop_;
    Condition cond_;
    MutexLock lock_;
    gNet::thread t_;
};

} // namespace Fnetgt

} // namespace gNet


#endif
