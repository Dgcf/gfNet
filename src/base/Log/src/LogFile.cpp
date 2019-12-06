#include "../inc/LogFile.h"

namespace gNet
{
    
LogFile::LogFile(unsigned int size, string sfile):
index_(0),
fileSize_(size ? size : 1024*1000),
unused_(fileSize_),
logFile_(sfile)
{
    open();
}

LogFile::~LogFile()
{
    fstrm_.close();
}

void LogFile::open()
{
    fstrm_.open(getfilename(), fstream::out | fstream::app);
}

void LogFile::write(const char* msg, unsigned int size)
{
    if (size > unused_)
    {
        unused_ = fileSize_;
        fstrm_.close();
        open();
    }
    
    fstrm_<< msg << "\n";
    unused_ -=  size;
}

string LogFile::getfilename()
{
    string filename = logFile_ + Timestamp::file_time() + ".log";
    return filename;
}

} // namespace gNet
