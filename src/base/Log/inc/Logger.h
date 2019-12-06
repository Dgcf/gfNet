#ifndef GFNET_LOG_LOGGER_H
#define GFNET_LOG_LOGGER_H

#include "../../../common/common.h"
#include "../inc/FixedBuffer.h"
#include "../inc/AsyncLogging.h"
#include "../../Time/inc/Timestamp.h"

namespace gNet
{

enum LOGLEVEL
{
    info,
    debug,
    warning,
    error,
    fatal
};

class Logger
{
public:
    NO_COPY(Logger)
    Logger(const char* sfile, unsigned int sline, LOGLEVEL slevel);
    ~Logger();

public:
    Logger& operator<<(const char*);
    static void SetLogLevel(LOGLEVEL slevel);

private:
    bool FilterLevel() { return static_cast<int>(level_)>=static_cast<int>(curlevel_); }
    void SwitchLogLevel(LOGLEVEL level);
    void LogInfo(const char* msg);

public:
    static AsyncLogging asyncLog_;
    static LOGLEVEL curlevel_;

private:
    static int count_;
    LOGLEVEL level_;
    char szLevel_[16];
    char szFile_[32];
    char logmsg_[128];
    FixedBuffer<g_smallsize> buffer_;
};

}


/************************************************************
 * Log格式：2019-01-01 00:00:00 PID TID level FIle xxxx
 * **********************************************************/
#define LOG_INFO                gNet::Logger(__FILE__, __LINE__, gNet::LOGLEVEL::info)
#define LOG_DEBUG           gNet::Logger(__FILE__, __LINE__, gNet::LOGLEVEL::debug)
#define LOG_WARNING     gNet::Logger(__FILE__, __LINE__, gNet::LOGLEVEL::warning)
#define LOG_ERROR           gNet::Logger(__FILE__, __LINE__, gNet::LOGLEVEL::error)
#define LOG_FATAL             gNet::Logger(__FILE__, __LINE__, gNet::LOGLEVEL::fatal)

static const char* s_test = "test_file";
static const unsigned int i_test = 10;
#define LOG_TEST               gNet::Logger(s_test, i_test, gNet::LOGLEVEL::info)                                      // for test

#endif
