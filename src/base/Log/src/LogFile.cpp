#include "../inc/LogFile.h"

namespace gNet
{
    
LogFile::LogFile(unsigned int size, string sfile):
index_(0),
fileSize_(size ? size : 1024*1000*10),
unused_(fileSize_),
logFile_(sfile),
fstrm_(logFile_)
{
    
}

LogFile::~LogFile()
{
    fstrm_.close();
}

void LogFile::open()
{

}

void LogFile::write(const char* msg, unsigned int size)
{
    if (size > unused_)
    {
        fstrm_.close();
        getfilename();
        fstrm_.open(logFile_, fstream::app);
    }
    
    fstrm_.write(msg, size);
    unused_ = fileSize_ - size;
}

void LogFile::getfilename()
{
    logFile_ += Timestamp::now();
    logFile_ += ".log";
}

} // namespace gNet
