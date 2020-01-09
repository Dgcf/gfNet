#ifndef GFNET_MEM_UNIWUEPTR_H
#define GFNET_MEM_UNIWUEPTR_H

#include <tuple>
#include <iostream>
using namespace std;

namespace gNet
{

template<typename _Tp>
struct default_delete
{
    void operator()(_Tp* __p) const
    {
        std::cout << "delete" << std::endl;
        delete __p;
        __p = nullptr;
    }
};

template<typename _Tp, typename _Dp>
class __uniq_ptr_impl
{
    template<typename _Up, typename _Ep>
    struct Ptr
    {
        typedef _Up* type; 
    };

public:
    typedef typename Ptr<_Tp, _Dp>::type pointer;

    // 默认初始化
    __uniq_ptr_impl()
    :_M_t()
    {
    }

    explicit __uniq_ptr_impl(pointer _p)
    :_M_t()
    {
        _M_ptr() = _p;
    }

    __uniq_ptr_impl(pointer __t, _Dp __p)
    :_M_t(__t, __p)
    {
    }

    ~__uniq_ptr_impl() {}

// 以下四个函数有可能抛出异常，所以不声明为noexpect
    pointer _M_ptr() const { return std::get<0>(_M_t); }

    pointer& _M_ptr() { return std::get<0>(_M_t); }

    // 应该返回什么类型？返回const引用
    const _Dp& _M_deleter() const { return std::get<1>(_M_t); }

    _Dp& _M_deleter() { return std::get<1>(_M_t); }
    

private:
    tuple<pointer, _Dp> _M_t;
};


template<typename _Tp, typename _Dp=default_delete<_Tp>>
class unique_ptr
{
public:
    template<typename _Yp>
    unique_ptr(const _Yp& _y) = delete;

    template<typename _Yp>
    unique_ptr& operator=(const _Yp& _y) = delete;

    typedef typename __uniq_ptr_impl<_Tp, _Dp>::pointer pointer;
    typedef _Tp element_type;
    typedef _Dp deleter_type;
    // using pointer = typename __uniq_ptr_impl<_Tp, _Dp>::pointer;

    // 默认构造
    unique_ptr() noexcept
    :_M_t(nullptr)
    {
    }

    // 构造
    explicit unique_ptr(pointer _p) noexcept
    :_M_t(_p)
    {
    }

//源码中加入类型萃取
    unique_ptr(pointer __p, _Dp __d) noexcept
    :_M_t(__p, __d)
    {
    }

    /***************************************************************
     * 移动构造
     * 
     * *************************************************************/
    unique_ptr(unique_ptr<_Tp, _Dp>&& __u) noexcept
    :_M_t(__u.release(), __u.get_deleter())
    {
    }

    ~unique_ptr() noexcept
    {
        auto& __ptr = _M_t._M_ptr();
        if (__ptr!=nullptr)
        {
            printf("reset ptr is %p\n", __ptr);
            get_deleter()(__ptr);
        }
    }

    pointer get() const { return _M_t._M_ptr(); }

    /*********************************************************
     * 获得unique_ptr拥有的对象并放弃该对象的拥有权
     * *******************************************************/
    pointer release()
    {
        pointer p = _M_t._M_ptr();
        _M_t._M_ptr() = nullptr;
        return p;
    }

    /********************************************************
     * 调用deleter释放
     * ******************************************************/
    void reset()
    {
        printf("reset ptr is %p\n", _M_t._M_ptr());
        get_deleter()(_M_t._M_ptr());
    }

    /********************************************************
     * 调用deleter释放之前的内存，重新指向传递给他的新地址
     * ******************************************************/
    void reset(pointer __p)
    {
        _M_t._M_deleter()(_M_t._M_ptr());
    }

    deleter_type& get_deleter()         // 如果是const函数，在reset()中无法调用
    {
        return _M_t._M_deleter();
    }

    const unique_ptr& operator=(unique_ptr<_Tp, _Dp>&& _u)
    {
        _M_t._M_deleter()(_M_t._M_ptr());
        _M_t(_u.release(), _u.get_deleter());
    }

    operator bool() const
    {
        return _M_t._M_ptr() != nullptr;
    }

    _Tp operator*()
    {
        return *_M_t._M_ptr();
    }

    _Tp operator->()
    {
        return *_M_t._M_ptr();
    }

private:
    __uniq_ptr_impl<_Tp, _Dp> _M_t;
};

} // namespace gNet

#endif
