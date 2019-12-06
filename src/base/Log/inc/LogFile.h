#ifndef GFNET_LOGFILE_H
#define GFNET_LOGFILE_H
#include <fstream>
#include "../../../common/common.h"
#include "../../Time/inc/Timestamp.h"

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
    LogFile(unsigned int size, string sfile="log1");
    ~LogFile();

    void open();
    void write(const char* msg, unsigned int size);
    void flush() { fstrm_.flush(); }

private:
    string getfilename();
    
private:
    unsigned int            index_;
    unsigned int            fileSize_;
    unsigned int            unused_;
    string                          logFile_;
    ofstream                    fstrm_;                     // 文件只在析构时被关闭
    Timestamp              timestamp_;
};

} // namespace gNet

#endif
