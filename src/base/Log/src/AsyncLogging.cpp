#include "../inc/AsyncLogging.h"

namespace gNet
{

AsyncLogging::AsyncLogging():
thread_(std::bind(&AsyncLogging::ThreadFunc, this), nullptr),
currentBuffer_(new FixedBuffer<g_bigsize>),
nextBuffer_(new FixedBuffer<g_bigsize>),
running_(false)
{
    // Start();
}

AsyncLogging::~AsyncLogging()
{
    if (running_)
    {
        Stop();
    }
    
}

void AsyncLogging::Append(const char* msg, unsigned int len)
{
    lock_.Lock();
    // printf("shengxia: %d, len is %d\n", currentBuffer_->avail(), len);
    if (currentBuffer_ && currentBuffer_->avail() > len)
    {
        currentBuffer_->Append(msg, len);          // 优先放到currentBuffer_中去,不需要每次都往buffers_里塞
    }
    else
    {
        // 这里为什么需要buffers_?
        // 1。如果notify之后数据不被消费，currentBuffer_是放不下的；2。是不是涉及到数据的频繁写入？
        
        buffers_.push_back(std::move(currentBuffer_)); 
        if (nextBuffer_)
        {
            currentBuffer_ = std::move(nextBuffer_);
        }
        else
        {
            currentBuffer_.reset(new FixedBuffer<g_bigsize>);
        }
        currentBuffer_->Append(msg, len); 
        cond_.Notify_One();
    }
    lock_.UnLock();
}

void AsyncLogging::Start()
{
    running_ = true;
    thread_.start();
}

void AsyncLogging::Stop()
{
    running_ = false;
    cond_.Notify_All();
    thread_.join();
}

void* AsyncLogging::ThreadFunc()
{
    std::unique_ptr<FixedBuffer<g_bigsize>> newBuffer1(new FixedBuffer<g_bigsize>);
    std::unique_ptr<FixedBuffer<g_bigsize>> newBuffer2(new FixedBuffer<g_bigsize>);
    newBuffer1->bZero();
    newBuffer2->bZero();
    std::vector<unique_ptr<FixedBuffer<g_bigsize>>> newBuffers;

    LogFile logfile(0, "./gftest");
    while (running_)
    {
        {
            MutexLockGuard lc(lock_);
            cond_.wait(lock_);

            // 不管currentBuffer_有没有满，都强行移到buffers_中; 
            // 如果在notify之后，还没有向currentBuffer写数据，这时候转移到buffers_似乎有问题？
            buffers_.push_back(std::move(currentBuffer_)); 

            #ifdef DEBUG
            for (vector<unique_ptr<FixedBuffer<g_bigsize>>>::const_iterator it = buffers_.begin(); it != buffers_.end(); ++it)
            {
                printf("buffers_ is %s————%d\n",(*it)->Data(), (*it)->DataSize());
            }
            #endif
            currentBuffer_ = std::move(newBuffer1);
            newBuffers.swap(buffers_);
            
            if (!nextBuffer_)
            {
                nextBuffer_ = std::move(newBuffer2);
            }
        }
        
        // 写文件
        for (vector<unique_ptr<FixedBuffer<g_bigsize>>>::const_iterator it = newBuffers.begin(); it != newBuffers.end(); ++it)
        {
            logfile.write((*it)->Data(), (*it)->DataSize());
        }
        logfile.flush();
        
        if (!newBuffer1)
        {
            assert(!newBuffers.empty());
            newBuffer1 = std::move(newBuffers.back());              // 要确保newBuffers里有空间可用
            newBuffers.pop_back();
            newBuffer1->reset();
        }

        if (!newBuffer2)
        {
            assert(!newBuffers.empty());
            newBuffer2 = std::move(newBuffers.back());
            newBuffers.pop_back();
            newBuffer2->reset();
        }
        newBuffers.clear();
    }
    
}

} // namespace gNet
