#ifndef GFNET_LOGO_ASYNCLOGGING_H
#define GFNET_LOGO_ASYNCLOGGING_H

#include "../../../common/common.h"
#include "../../Thread/inc/Mutex.h"
#include "../../Thread/inc/Condition.h"
#include "../../Thread/inc/thread.h"
#include "./FixedBuffer.h"
#include "./LogFile.h"

namespace gNet
{


class AsyncLogging
{
public:
    NO_COPY(AsyncLogging)

    AsyncLogging();
    ~AsyncLogging();
public:
    void Append(const char* msg, unsigned int len);
    void Start();
    void Stop();

private:
    void* ThreadFunc();

private:
    bool running_;
    MutexLock lock_;
    Condition cond_;
    thread thread_;
    std::unique_ptr<FixedBuffer<g_bigsize>> currentBuffer_;
    std::unique_ptr<FixedBuffer<g_bigsize>> nextBuffer_;
    std::vector<unique_ptr<FixedBuffer<g_bigsize>>> buffers_;
};

}

#endif
