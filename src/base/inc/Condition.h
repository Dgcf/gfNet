#include "Mutex.h"

namespace gNet
{

class Condition
{
public:
    NO_COPY(Condition)

public:
    Condition();
    ~Condition();

    template<typename _Predicate>
    void Wait(MutexLockGuard& lock, _Predicate __p);

    void wait(MutexLockGuard& lock);
    
    void Notify_One();
    void Notify_All();

public:

private:
    //MutexLockGuard   lockguard_;
    pthread_cond_t cond_;
};

}
