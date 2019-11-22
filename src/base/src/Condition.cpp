#include "../inc/Condition.h"

Condition::Condition()
{
    GF_CHECK(pthread_cond_init(&cond_, NULL))
}

Condition::~Condition()
{
    GF_CHECK(pthread_cond_destroy(&cond_))
}

// 设想为实现C++11中的condition_variable中的wait，配合gunique_lock使用，但是。。。
// TODO
template<typename _Predicate>
void Condition::Wait(MutexLockGuard& lock, _Predicate __p)
{
    if (!__p())
    {
        // 如果条件不满足，先解锁，再等待
        // lock.release();
        GF_CHECK(pthread_cond_wait(&cond_, lock.getMutex()))
    }
}

void Condition::wait(MutexLockGuard& lock)
{
    GF_CHECK(pthread_cond_wait(&cond_, lock.getMutex()));
}

void Condition::Notify_One()
{
    GF_CHECK(pthread_cond_signal(&cond_))
}

void Condition::Notify_All()
{
    GF_CHECK(pthread_cond_broadcast(&cond_))
}