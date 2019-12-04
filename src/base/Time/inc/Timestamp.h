#ifndef GFNET_TIMESTAMP_H
#define GFNET_TIMESTAMP_H

#include "../../../common/common.h"
#include <string.h>
#include <sys/time.h>
#include <ctime>
using namespace std;

namespace gNet
{

class Timestamp
{
private:
    static char current_time_[32];
    static char file_time_[32];
public:
    Timestamp(/* args */);
    ~Timestamp();

    static const char* now();
    static const char* file_time();
};


}

#endif
