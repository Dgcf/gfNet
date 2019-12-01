#include "../inc/Timestamp.h"

namespace gNet
{

const char* Timestamp::now()
{
    timeval val;
    memset(&val, 0, sizeof(val));
    gettimeofday(&val, NULL);

    struct tm* ptm;
    char time_string[32];
    char current_time[32];
     ptm = localtime(&val.tv_sec);
     long milliseconds = val.tv_usec / 1000;
     strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", ptm);
     sprintf(current_time, "%s %3ld", time_string, milliseconds);
     return current_time;
}

Timestamp::Timestamp(/* args */)
{
}

Timestamp::~Timestamp()
{
}



}
