#include "../inc/Mutex.h"

namespace gNet
{

MutexLock::MutexLock()
{
    GF_CHECK(pthread_mutex_init(&mutex_, NULL))
}

MutexLock::~MutexLock()
{
    GF_CHECK(pthread_mutex_destroy(&mutex_))
}

void MutexLock::Lock()
{
    GF_CHECK(pthread_mutex_lock(&mutex_))
}

void MutexLock::UnLock()
{
    GF_CHECK(pthread_mutex_unlock(&mutex_))
}

MutexLockGuard::MutexLockGuard()
{
    lock_.Lock();
}

MutexLockGuard::~MutexLockGuard()
{
    if (!release_)
    {
        lock_.UnLock();
    }
}

}
