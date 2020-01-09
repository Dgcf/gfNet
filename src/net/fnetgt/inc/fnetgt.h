#ifndef GFNET_FNETGET_H_
#define GFNET_FNETGET_H_

#include <functional>
// #include "./TcpConnection.h"
namespace gNet
{

namespace Fnetgt
{

class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
/*********************************************************
 * 回调函数对象
 ********************************************************/

// 建立新连接回调
typedef std::function<void()> NewConnnectionCallback;

// 消息回调
typedef std::function<void(const TcpConnectionPtr& _ptr, const char* _msg, int _len)> MessageCallback;

// 关闭连接回调
typedef std::function<void(const TcpConnectionPtr& _ptr)> CloseCallback;

}


}


#endif
