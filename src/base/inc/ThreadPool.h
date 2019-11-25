#ifndef GFNET_THREADPOOL_H
#define GFNET_THREADPOOL_H

#include <future>
#include <functional>
#include <vector>
#include <list>
#include <memory>
#include "../inc/thread.h"
#include "../inc/Mutex.h"
#include "../inc/Condition.h"
#include "../../common.h"

using namespace std;

namespace gNet
{

typedef void (*callback_)(void* );
typedef std::function<void(void*)> Task;

class ThreadPool
{
public:
    NO_COPY(ThreadPool)
    typedef std::function<void*(void*)> func_type;


public:
    ThreadPool(int nums, void *data);
    void start();
    void AddTask(MsgType<Task>& task);
    Task GetTask();

private:
    void* RunInThread();

private:
    //thread thread_;
    int num_;
    func_type func_;
    void* data_;
    // 因为thread不能拷贝，所以采用指针保存
    vector<unique_ptr<gNet::thread> > threads_;

    // 任务llist
    list<MsgType<Task>> tasks_;
    Condition cond_;
    bool quit_;
};

}

#endif
