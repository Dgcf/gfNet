#include <thread>
#include <future>
#include <condition_variable>
#include <deque>
#include <list>
#include "./Condition.h"
#include  "../../../common/common.h"

using namespace std;

namespace gNet
{

/*********************************************
 * 支持优先级排序的消息队列
 * *******************************************/
template<typename _Ty>
class MsgQueue
{
private:
    list<MsgType<_Ty> > queue_;
    Condition cond_;

public:
    MsgQueue();
    ~MsgQueue();

public:
    void add(MsgType<_Ty>& msg);
    _Ty get();

private:
    MutexLock  lock_;
};

template<typename _Ty>
MsgQueue<_Ty>::MsgQueue()
{
}

template<typename _Ty>
MsgQueue<_Ty>::~MsgQueue()
{
}

template<typename _Ty>
void MsgQueue<_Ty>::add(MsgType<_Ty>& msg)
{
    MutexLockGuard lc(lock_);                // 如果用这个，会出现崩溃，从打印看没有锁住资源
    queue_.push_back(msg);
    printf("queue_.size(): %ld\n", queue_.size());
    
    // 排序还有问题：
    // 1。语法问题；2。gdb调试问题，两个问题都是无法打印queue_内容
    queue_.sort(); 
    
    #ifdef DEBUG
    for (typename list<MsgType<_Ty> >::iterator it = queue_.begin(); it != queue_.end(); ++it)
    {
        printf("priority: %d, msg is %s\n", it->priority_,it->msg_.c_str());
    }
    #endif

    //cond_.Notify_One();
}

template<typename _Ty>
_Ty MsgQueue<_Ty>::get()
{
    MutexLockGuard lc(lock_);
    if (queue_.empty())
    {
        cond_.wait(lock_);
    }
    MsgType<_Ty> ty = queue_.front();
    queue_.pop_front();
    return ty.msg_;
}

}
