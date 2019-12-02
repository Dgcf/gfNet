#ifndef GFNET_LOG_FIXEDBUFFER_H
#define GFNET_LOG_FIXEDBUFFER_H

#include "../../../common/common.h"

namespace gNet
{

/***************************************************************************************
 * 存放打印到终端的log
 * size的指定可以用非类型模板，也可以在构造/方法中指定，两种方法有什么优缺点？TODO
 * **************************************************************************************/
template<unsigned int size>
class FixedBuffer
{
public:
    NO_COPY(FixedBuffer)

    FixedBuffer() { cur_ = data_; }
public:
    void Append(const char* msg, unsigned int len);
    char* Data() { return data_; }
    unsigned int dataSize() { static_cast<unsigned int>(cur_-data_); }
    unsigned int avail() { data_+sizeof(data_) - cur_;}
    void reset() { cur_ = data_; }

private:
    char data_[size];       // 总空间大小
    char* cur_;                  // 当前空闲空间的位置
};

}

#endif
