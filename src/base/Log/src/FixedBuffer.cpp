#include <string.h>
#include "../inc/AsyncLogging.h"

namespace gNet
{

template<unsigned int size>
void FixedBuffer<size>::Append(const char* msg, unsigned int len)
{
    memcpy(cur_, msg, len);
    cur_ = cur_ + len;
}

}