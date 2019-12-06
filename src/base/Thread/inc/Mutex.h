#ifndef GFNET_MUTEX_H
#define GFNET_MUTEX_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include  "../../../common/common.h"

namespace gNet
{

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
    MutexLock& lock_;
    bool release_;

public:
    MutexLockGuard(MutexLock& lock);
    ~MutexLockGuard();
    void release() 
    { 
        lock_.UnLock(); 
        release_ = true;
    }
    pthread_mutex_t* getMutex() { return lock_.getMutex(); }
};

}

#endif
