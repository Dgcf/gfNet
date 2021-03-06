#include "../inc/thread.h"
namespace gNet
{

void* thread::ThreadCallBack(void *args)
{
    thread* t = static_cast<thread*>(args);
    t->CallBack();
}

void thread::CallBack()
{
    if (func_)
    {
        func_();
    }
}

thread::thread(func_type func, void* args):
threadID(0),
func_(func),
data_(args)
{
}

void thread::start()
{
    GF_CHECK(pthread_create(&threadID, NULL, &thread::ThreadCallBack, this));
}

void thread::detach()
{
    GF_CHECK(pthread_detach(threadID));
}

void thread::join()
{
    GF_CHECK(pthread_join(threadID, NULL));
    
}

namespace CurrentThread
{

string ICurrentthreadID()
{
    char strpid[32];
    memset(strpid, 0, sizeof(strpid));
    pid_t pid = syscall(SYS_gettid);
    sprintf(strpid, "%5d", (int)pid);
    return strpid;
}

}

}
