#include "/home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/inc/Channel.h"

namespace gNet
{

namespace Fnetgt
{

Channel::Channel(int _f, std::shared_ptr<EventLoop> _l):
events_(0),
curevents_(0),
lp_(_l),
fd_(_f)
{

}

void Channel::Update()
{
    lp_->Update(fd_,events_, this);
}

void Channel::HandleEvent()
{
   if (curevents_ & EPOLLIN && readCallback_)                       // 读事件
   {
       readCallback_();
   }
   else if (curevents_ & EPOLLOUT && writeCallback_)        // 写事件
   {
       writeCallback_();
   }
   else if(curevents_ & EPOLLERR && errorCallback_)         // 错误事件
   {
       errorCallback_();
   }
   else if (curevents_ & EPOLLRDHUP && closeCallback_)  // 断开连接或半关闭的情况
   {
       closeCallback_();
   }
}

} // namespace Fnetgt

} // namespace gNet
