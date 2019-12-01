#ifndef GFNET_LOGFILE_H
#define GFNET_LOGFILE_H

#include "../../../common/common.h"

namespace gNet
{

/********************************************
 * 打开文件，写文件，新增文件，关闭文件
 * 负责自动换写文件
 * ******************************************/
class LogFile
{
public:
    NO_COPY(LogFile)

public:
    LogFile();
    ~LogFile();

    void open();
    void write(const char* msg, unsigned int size);
    
private:
    char logFile_[64];
    fstream fstrm;
};

} // namespace gNet

#endif
