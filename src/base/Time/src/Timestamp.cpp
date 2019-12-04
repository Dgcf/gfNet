#include "../inc/Timestamp.h"

namespace gNet
{

char Timestamp::current_time_[32];
char Timestamp::file_time_[32];

const char* Timestamp::now()
{
    timeval val;
    memset(&val, 0, sizeof(val));
    gettimeofday(&val, NULL);

    struct tm* ptm;
    char time_string[32];
    
     ptm = localtime(&val.tv_sec);
     long milliseconds = val.tv_usec / 1000;
     strftime(time_string, sizeof(time_string), "%Y%m%d-%H%M%S", ptm);
     sprintf(current_time_, "%s %3ld", time_string, milliseconds);
     return current_time_;
}

const char* Timestamp::file_time()
{
    time_t t;
    std::time(&t);
    struct tm* tv = std::localtime(&t);
    std::strftime(file_time_, sizeof(file_time_), "%Y-%m-%d %H:%M:%S", tv);
    return file_time_;
}

Timestamp::Timestamp(/* args */)
{
}

Timestamp::~Timestamp()
{
}



}
