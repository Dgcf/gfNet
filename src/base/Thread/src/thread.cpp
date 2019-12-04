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
    pthread_create(&threadID, NULL, &thread::ThreadCallBack, this);
}

void thread::detach()
{
    pthread_detach(threadID);
}

void thread::join()
{
    pthread_join(threadID, NULL);
}

namespace CurrentThread
{

string ICurrentthreadID()
{
    return "";
}

}

}
