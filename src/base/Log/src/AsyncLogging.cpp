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
    if (!currentBuffer_ && sizeof(*msg) > currentBuffer_->avail())
    {
        if (!nextBuffer_)
        {
            // std::unique_ptr<FixedBuffer<g_bigsize>> su(new FixedBuffer<g_bigsize>);
            // nextBuffer_ = std::move(su);
            currentBuffer_.reset(new FixedBuffer<g_bigsize>);
        }
        else
        {
            currentBuffer_ = std::move(nextBuffer_);    
        }
    }
    currentBuffer_->Append(msg, sizeof(*msg));
    buffers_.push_back(std::move(currentBuffer_));
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
        newBuffers.swap(buffers_);
        lock_.UnLock();

        // 写文件
        LogFile logfile;
        for (vector<unique_ptr<FixedBuffer<g_bigsize>>>::const_iterator it = newBuffers.begin(); it != newBuffers.end(); ++it)
        {
            logfile.write((*it)->Data(), (*it)->dataSize());
        }
        
        lock_.Lock();
        // TODO
    }
    
}

} // namespace gNet
