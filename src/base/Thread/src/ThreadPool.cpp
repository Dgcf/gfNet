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

ThreadPool::~ThreadPool()
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
        threads_[i]->start();
    }
}

void ThreadPool::stop()
{
    quit_ = true;
    cond_.Notify_All();
    for (vector<unique_ptr<gNet::thread> >::iterator iter = threads_.begin(); iter != threads_.end(); ++iter)
    {
        (*iter)->join();
    }
}

void ThreadPool::AddTask(MsgType<Task>& task)
{
    // 根据优先级先排序
    MutexLockGuard lc(mutex_);
    tasks_.push_back(task);
    tasks_.sort();
    cond_.Notify_One();
}

Task ThreadPool::GetTask()
{
    MutexLockGuard lc(mutex_);
    Task func;
    if (!tasks_.empty())
    {
        MsgType<Task> task = tasks_.front();
        tasks_.pop_front();
        func = task.msg_;
    }
    return func;
}

void* ThreadPool::RunInThread()
{
    while (!quit_)
    {
        {
            MutexLockGuard lc(mutex_);
            if(tasks_.empty())
            {
                cond_.wait(mutex_);
            }
        }
        Task task = GetTask();
        if (task)
        {
            task(nullptr);
        }
    }
    
    #ifdef DEBUG
    printf("*********************pthread join: %s************************\n", CurrentThread::ICurrentthreadID().c_str());
    #endif
}

}
