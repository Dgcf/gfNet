#include <pthread.h>
#include  "../../common.h"

namespace gNet
{

typedef void (*ThreadFunc)(void*);

class thread
{
public:
    NO_COPY(thread)
    typedef std::function<void*(void*)> func_type;

public:
    thread(func_type func, void* args);
    void detach();
    void join();
    void CallBack();

private:
    static void* ThreadCallBack(void *);

private:
    pthread_t threadID;
    func_type func_;
    void *data_;
};

}