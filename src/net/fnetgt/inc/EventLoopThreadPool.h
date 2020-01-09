#ifndef GFNET_FNETGT_EVENTLOOPTHREADPOOL_H_
#define GFNET_FNETGT_EVENTLOOPTHREADPOOL_H_

#include "../../../common/common.h"
#include "./EventLoopThread.h"

namespace gNet
{
    
namespace Fnetgt
{
    
class EventLoopThreadPool
{
public:
    EventLoopThreadPool();
    ~EventLoopThreadPool();
    void Start();
    EventLoop* GetNextLoop();

private:
    std::vector<EventLoopThread*> threads_;
    std::vector<EventLoop*>   loops_;
    int next_;
};

} // namespace Fnetgt

} // namespace gNet

#endif
