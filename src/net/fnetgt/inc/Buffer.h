#ifndef GFNET_FNETGT_BUFFER_H_
#define GFNET_FNETGT_BUFFER_H_

#include "../../../common/common.h"
#include <sys/socket.h>
#include <sys/uio.h>

namespace gNet
{

namespace Fnetgt
{

class Buffer
{
public:
    NO_COPY(Buffer)
    Buffer() { }

    int WriteableBytes() { buffer_.size() - writeIndex_; }
    int ReadableBytes() { writeIndex_ - readIndex_; }
    void MakeSpace(int _l);
    void ReadFd();
    void WriteFd();
    char* begin() { return &*buffer_.begin(); }
    void Append(const char* _d, int _l);
    void CompleteRead() { readIndex_ = writeIndex_; }
    char* peek() { return begin() + readIndex_; }

private:
    int fd_;
    int prependable_;
    int  readIndex_;
    int writeIndex_;
    std::vector<char> buffer_;
};

} // namespace Fnetgt

} // namespace gNet


#endif
