#include "../inc/Timer.h"

namespace gNet
{


void Timer::timer_out(__sigval_t v)
{
    Timer* t = static_cast<Timer*>(v.sival_ptr);
    t->func_();
}

Timer::Timer(unsigned int val, FuncType func):
timerid_(0),
func_(func)
{
    ZeroMemory(evp_);
    evp_.sigev_notify = SIGEV_THREAD;
    evp_.sigev_value.sival_ptr = this;
    evp_.sigev_notify_function = Timer::timer_out;
    GF_CHECK(timer_create(CLOCK_REALTIME, &evp_, &timerid_));

    ZeroMemory(ts_);
    ts_.it_value.tv_sec = val;

    GF_CHECK(timer_settime(timerid_, 0, &ts_, NULL));
}

Timer::~Timer()
{
    timer_delete(timerid_);
    timerid_ = 0;
}


} // namespace gNet
