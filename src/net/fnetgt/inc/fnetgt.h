#ifndef GFNET_FNETGET_H_
#define GFNET_FNETGET_H_

#include <functional>
/*********************************************************
 * 回调函数对象
 ********************************************************/

// 建立新连接回调
typedef std::function<void()> NewConnnectionCallback;

// 消息回调
typedef std::function<void(const char* _msg)> MessageCallback;

#endif
