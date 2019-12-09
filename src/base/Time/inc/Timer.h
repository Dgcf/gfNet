#ifndef GFNET_TIMER_H
#define GFNET_TIMER_H

#include "../../../common/common.h"
#include <signal.h>
#include <time.h>


namespace gNet
{
    
class Timer
{
public:
    NO_COPY(Timer)
    Timer(unsigned int val, FuncType func);
    ~Timer();

    static void timer_out(sigval v);
    void settime(){}

private:
    FuncType                         func_;
    timer_t                             timerid_;
    struct sigevent              evp_; 
    struct itimerspec         ts_;
};

} // namespace gNet


#endif
