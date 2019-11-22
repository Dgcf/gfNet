#include <thread>
#include <future>
#include <condition_variable>
#include <deque>
#include <list>
#include "./Condition.h"
#include "../../common.h"

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
    MutexLockGuard lc;
    queue_.push_back(msg);
    queue_.sort();
    cond_.Notify_One();
}

template<typename _Ty>
_Ty MsgQueue<_Ty>::get()
{
    MutexLockGuard lc;
    if (queue_.empty())
    {
        cond_.wait();
    }
    MsgType<_Ty> ty = queue_.front();
    queue_.pop_front();
    return ty.msg_;
}

}
