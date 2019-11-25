#include "../inc/ThreadPool.h"

namespace gNet
{

ThreadPool::ThreadPool(int nums, void*data):
num_(nums),
data_(data),
quit_(false)
//thread_(func_, data)
{

}

void ThreadPool::start()
{
    for (size_t i = 0; i < num_; i++)
    {
        // 两种方法：
        // unique_ptr<gNet::thread> t(new gNet::thread(std::bind(&ThreadPool::RunInThread, this), data_));
        // threads_.push_back(std::move(t));
        threads_.emplace_back(new gNet::thread(std::bind(&ThreadPool::RunInThread, this), data_));
    }
}

void ThreadPool::AddTask(MsgType<Task>& task)
{
    // 根据优先级先排序
    MutexLockGuard lockguard;
    tasks_.push_back(task);
    tasks_.sort();
    cond_.Notify_One();
}

Task ThreadPool::GetTask()
{
    MutexLockGuard lc;
    MsgType<Task> task = tasks_.front();
    tasks_.pop_front();
    return task.msg_;
}

void* ThreadPool::RunInThread()
{
    while (!quit_)
    {
        MutexLockGuard lc;
        if(tasks_.empty())
        {
            cond_.wait(lc);
        }
        GetTask();
    }
}

}
