#include "../inc/Logger.h"

namespace gNet
{
    
AsyncLogging Logger::asyncLog_ ;
LOGLEVEL Logger::curlevel_ = info;
int Logger::count_ = 0;

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
    // printf("count is: %d\n", ++count_);
    asyncLog_.Append(buffer_.Data(), buffer_.DataSize());
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
        strncpy(szLevel_, "INFO", sizeof(szLevel_));
        break;
    case debug:
        strncpy(szLevel_, "DEBUG", sizeof(szLevel_));
        break;
    case warning:
        strncpy(szLevel_, "WARNING", sizeof(szLevel_));
        break;
    case error:
        strncpy(szLevel_, "ERROR", sizeof(szLevel_));
        break;
    case fatal:
        strncpy(szLevel_, "FATAL", sizeof(szLevel_));
        break;
    default:
        break;
    }
}

void Logger::LogInfo(const char* msg)
{
    //                            time/PID/level/file/msg
    sprintf(logmsg_, "%s %s %-7s %-18s: %s", Timestamp::file_time(), CurrentThread::ICurrentthreadID().c_str(), szLevel_, szFile_, msg);
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
