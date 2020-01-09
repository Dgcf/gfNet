#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/Buffer.h"

namespace gNet
{

namespace Fnetgt
{

Buffer::Buffer():
prependable_(8),
readIndex_(8),
writeIndex_(8),
initialsize_(1024),
buffer_(prependable_+initialsize_)
{

}

void Buffer::MakeSpace(int _l)
{
    if (_l <= readIndex_ - prependable_ + WriteableBytes())
    {
        std::copy(buffer_.begin()+readIndex_, buffer_.begin()+writeIndex_, buffer_.begin()+prependable_);
        writeIndex_ = writeIndex_-(readIndex_-prependable_);
        readIndex_ = prependable_;
    }
    else    // buffer不够，需要扩容
    {
        buffer_.resize(buffer_.size()+_l);
    }
}

unsigned int Buffer::ReadFd(int _f)
{
    char extrabuffer[65536];
    const int writeable = WriteableBytes();
    // printf("writeable is %d\n", writeable);
    iovec vec[2];
    vec[0].iov_base = begin() + writeIndex_;
    vec[0].iov_len = writeable;
    vec[1].iov_base = extrabuffer;
    vec[1].iov_len = sizeof(extrabuffer);
    const size_t n = readv(_f, vec, 2);
    if (n<0)
    {
        // error
    }
    else if(n <= writeable)
    {
        writeIndex_ += n;
    }
    else
    {
        MakeSpace(n-writeable);
        std::copy(extrabuffer, extrabuffer+n-writeable, begin()+writeIndex_+writeable);
        writeIndex_ += n;
    }
    return n;
}

void Buffer::WriteFd()
{

}

void Buffer::Append(const char* _d, int _l)
{
    std::copy(_d, _d+_l, begin()+writeIndex_);
}

} // namespace Fnetgt

} // namespace gNet
