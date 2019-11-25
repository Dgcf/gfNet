#ifndef GFNET_SINGLETON_H
#define GFNET_SINGLETON_H

#include "Mutex.h"

template<typename _Ty>
class Singleton
{
private:
    _Ty ty;
public:
    Singleton() = delete;
    ~Singleton();

    _Ty* getInstance()
    {
        static _Ty ty;
        return &ty;
    }
};

#endif
