#include "../inc/LogFile.h"

namespace gNet
{
    
LogFile::LogFile():
fstrm(logFile_)
{
}

LogFile::~LogFile()
{
    fstrm.close();
}

void LogFile::open()
{

}

void LogFile::write(const char* msg, unsigned int size)
{
    fstrm.write(msg, size);
}

} // namespace gNet
