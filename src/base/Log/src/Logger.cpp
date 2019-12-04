#include "../inc/Logger.h"

namespace gNet
{
    
AsyncLogging Logger::asyncLog_ ;
LOGLEVEL Logger::curlevel_;

Logger::Logger(const char* sfile, unsigned int sline, LOGLEVEL slevel):
level_(slevel)
{
    memset(szLevel_, 0, sizeof(szLevel_));
    memset(szFile_, 0, sizeof(szFile_));
    SwitchLogLevel(level_);
    strncpy(szFile_, sfile, sizeof(szFile_));
}

Logger::~Logger()
{
    asyncLog_.Append(buffer_.Data());
}

void Logger::SetLogLevel(LOGLEVEL slevel)
{
    curlevel_ = slevel;
}

void Logger::SwitchLogLevel(LOGLEVEL level)
{
    switch (level)
    {
    case info:
        strncpy(szLevel_, "info", sizeof(szLevel_));
        break;
    case debug:
        strncpy(szLevel_, "debug", sizeof(szLevel_));
        break;
    case warning:
        strncpy(szLevel_, "warning", sizeof(szLevel_));
        break;
    case error:
        strncpy(szLevel_, "error", sizeof(szLevel_));
        break;
    case fatal:
        strncpy(szLevel_, "fatal", sizeof(szLevel_));
        break;
    default:
        break;
    }
}

void Logger::LogInfo(const char* msg)
{
    //                            time/PID/level/file/msg
    sprintf(logmsg_, "%s %s %s %s: %s\n", Timestamp::file_time(), CurrentThread::ICurrentthreadID().c_str(), szLevel_, szFile_, msg);
}

Logger& Logger::operator<<(const char* msg)
{
    if (FilterLevel())
    {
        LogInfo(msg);
        buffer_.Append(logmsg_, sizeof(logmsg_));
    }
    return *this;
}

} // namespace gNet
