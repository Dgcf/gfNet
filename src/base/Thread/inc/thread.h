#ifndef GFNET_THREAD_H
#define GFNET_THREAD_H

#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <pthread.h>
#include  "../../../common/common.h"

namespace gNet
{

typedef void (*ThreadFunc)(void*);

class thread
{
public:
    NO_COPY(thread)
    typedef std::function<void*()> func_type;

public:
    thread(func_type func, void* args);
    void start();
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

/*********************************************************************************
 * 可以封装成一个类来表示当前线程的一些属性，但需要构造实例，也可以用静态函数
 * 但这里选择命名空间表示
 * *******************************************************************************/
namespace CurrentThread
{

// 在这里定义会报错，必须在此声明，在cpp文件中定义
string ICurrentthreadID();

}

}

#endif
