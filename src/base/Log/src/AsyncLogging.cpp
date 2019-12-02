#include "../inc/AsyncLogging.h"

namespace gNet
{

AsyncLogging::AsyncLogging():
thread_(std::bind(&AsyncLogging::ThreadFunc, this), nullptr),
currentBuffer_(new FixedBuffer<g_bigsize>),
nextBuffer_(new FixedBuffer<g_bigsize>)
{
    Start();
}

void AsyncLogging::Append(const char* msg)
{
    lock_.Lock();
    // if (!currentBuffer_ && sizeof(*msg) > currentBuffer_->avail())
    // {
    //     if (!nextBuffer_)
    //     {
    //         // std::unique_ptr<FixedBuffer<g_bigsize>> su(new FixedBuffer<g_bigsize>);
    //         // nextBuffer_ = std::move(su);
    //         currentBuffer_.reset(new FixedBuffer<g_bigsize>);
    //     }
    //     else
    //     {
    //         currentBuffer_ = std::move(nextBuffer_);    
    //     }
    // }

    if (currentBuffer_ && currentBuffer_->avail() > sizeof(*msg))
    {
        currentBuffer_->Append(msg, sizeof(*msg));          // 优先放到currentBuffer_中去,不需要每次都往buffers_里塞
    }
    else
    {
        buffers_.push_back(std::move(currentBuffer_)); 
        if (nextBuffer_)
        {
            currentBuffer_ = std::move(nextBuffer_);
        }
        else
        {
            currentBuffer_.reset(new FixedBuffer<g_bigsize>);
        }
    
    }
    lock_.UnLock();
}

void AsyncLogging::Start()
{
    thread_.start();
}

void* AsyncLogging::ThreadFunc()
{
    std::unique_ptr<FixedBuffer<g_bigsize>> newBuffer1(new FixedBuffer<g_bigsize>);
    std::unique_ptr<FixedBuffer<g_bigsize>> newBuffer2(new FixedBuffer<g_bigsize>);
    std::vector<unique_ptr<FixedBuffer<g_bigsize>>> newBuffers;

    while (true)
    {
        lock_.Lock();
        buffers_.push_back(std::move(currentBuffer_));         // 在这里，不管currentBuffer_有没有满，都强行移到buffers_中
        newBuffers.swap(buffers_);
        currentBuffer_ = std::move(newBuffer1);
        if (!nextBuffer_)
        {
            nextBuffer_ = std::move(newBuffer2);
        }
        
        lock_.UnLock();

        // 写文件
        LogFile logfile;
        for (vector<unique_ptr<FixedBuffer<g_bigsize>>>::const_iterator it = newBuffers.begin(); it != newBuffers.end(); ++it)
        {
            logfile.write((*it)->Data(), (*it)->dataSize());
        }
        
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
    }
    
}

} // namespace gNet
