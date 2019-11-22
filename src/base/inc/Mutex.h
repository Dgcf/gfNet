#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../common.h"

#define GF_CHECK(x) { decltype(x) t = x;            \
                    assert(t == 0);                                             \
                 }

/*********************************************************
 * 封装pthread_mutex_t
 * *******************************************************/
class MutexLock
{
public:
    NO_COPY(MutexLock)

private:
    pthread_mutex_t mutex_;

public:
    MutexLock();
    ~MutexLock();
    void Lock();
    void UnLock();
    pthread_mutex_t* getMutex() { return & mutex_; }
};

class MutexLockGuard
{
public:
    NO_COPY(MutexLockGuard)

private:
    MutexLock lock_;
    bool release_;

public:
    MutexLockGuard();
    ~MutexLockGuard();
    void release() 
    { 
        lock_.UnLock(); 
        release_ = true;
    }
    pthread_mutex_t* getMutex() { return lock_.getMutex(); }
};

