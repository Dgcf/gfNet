#ifndef GFNET_TIMESTAMP_H
#define GFNET_TIMESTAMP_H

#include "../../../common/common.h"
#include <string.h>
#include <sys/time.h>

namespace gNet
{

class Timestamp
{
private:
    /* data */
public:
    Timestamp(/* args */);
    ~Timestamp();

    static const char* now();
};


}

#endif
