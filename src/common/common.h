#ifndef GFNET_COMMON_H
#define GFNET_COMMON_H

#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <memory>
#include <thread>
#include <future>
#include <condition_variable>
#include <functional>
#include <algorithm>
#include <string>
#include <chrono>
#include <fstream>

using namespace std;


#define NO_COPY_CONSTRUCTOR(MYCLASS) MYCLASS(const MYCLASS&) = delete;
 #define NO_COPY_OPERATOR(MYCLASS) MYCLASS& operator=(const MYCLASS&) = delete;
 #define NO_COPY(MYCLASS) NO_COPY_CONSTRUCTOR(MYCLASS)  \
                                                             NO_COPY_OPERATOR(MYCLASS)

namespace gNet
{

const int g_smallsize = 1024;
const int g_bigsize = 1024*1000;

#define GF_CHECK(x) { decltype(x) t = x;            \
                    assert(t == 0);                                             \
                 }

enum Priority
{
    Unknown,
    High,
    Mid,
    Usual,
    Last
};

template<typename _type>
struct MsgType
{
    Priority priority_;
    _type msg_;

    bool operator<(MsgType<_type>& _t)
    {
        return (int)priority_< (int)_t.priority_;
    }
};


}

#endif
