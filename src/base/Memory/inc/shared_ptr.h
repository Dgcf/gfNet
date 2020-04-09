#ifndef GFNET_MEM_SHAREDPTR_H
#define GFNET_MEM_SHAREDPTR_H

#include <stdint.h>
#include <iostream>
using namespace std;
namespace gNet
{

/****************************************************************
 * 负责管理计数
 * **************************************************************/
class _Sp_counted_base
{
public:
    _Sp_counted_base():
    use_count_(1)
    {
        // std::cout << use_count_ << std::endl;
    }

    void add_ref_lock()
    {
        //__atomic_fetch_add(&use_count_, 1);
        __sync_fetch_and_add(&use_count_, 1);
        // __atomic_fetch_add(&use_count_, 2); 这个系列的函数在哪查找？
    }

    void add_ref_copy()
    {
        __gnu_cxx::__atomic_add_dispatch(&use_count_, 1);
    }

    void minus_ref_lock()
    {
        release();
    }

    virtual void dispose() = 0;

    void release()
    {
        // std::cout << "~_Sp_counted_base" << std::endl;
        //std::cout << << std::endl;
        if(1 ==__gnu_cxx::__exchange_and_add_dispatch(&use_count_, -1) )       // 调用__exchange_and_add_dispatch前必须加上作用域__gnu_cxx
        {
            dispose();
            destroy();
        }
    }

    void destroy()                  // 销毁自己
    {
        delete this;
    }

    // 不是线程安全的。。 TODO
    unsigned int get_use_count() const { return use_count_; }

    virtual ~_Sp_counted_base()
    {
        // std::cout << use_count_ << std::endl;
    }

    unsigned int getcount() { return use_count_; }

private:
    _Atomic_word use_count_;            // use_count必须时原子操作
};

/*****************************************************************
 * 负责管理指针
 * 问题：
 * 1。访问父类引用计数；
 * 2。析构时要先知道父类中的引用计数，再决定要不要delete，但父类的引用计数是在析构的是否-1的，先析构子类，这不就矛盾了吗
 * ***************************************************************/
template<typename _Ptr>
class _Sp_counted_ptr:  public _Sp_counted_base
{
public:
    _Sp_counted_ptr(_Ptr* ptr): _Sp_counted_base(),
    ptr_(ptr)
    {
    }

    // 拷贝构造：
    _Sp_counted_ptr( _Sp_counted_ptr& lptr):
    _Sp_counted_base(lptr),
    ptr_(lptr.ptr_)
    {
        // std::cout << "_Sp_counted_ptr copy" << std::endl;
    }

    ~_Sp_counted_ptr()
    {
        // std::cout << "~_Sp_counted_ptr" << std::endl;
    }

    void dispose()
    {
        if (ptr_)
        {
            printf("ptr address is: %p\n", ptr_);
            delete ptr_;
            ptr_ = nullptr;   
        }
    }

private:
    _Ptr* ptr_;
};

/****************************************************************
 * 负责管理指针，引用计数
 * **************************************************************/
class __shared_count
{
public:
    __shared_count():base_(0) {}

    template<typename _Tp>
    __shared_count(_Tp* tp):
    base_(new _Sp_counted_ptr<_Tp>(tp))
    {
        // std::cout << "template<typename _Tp>__shared_count(_Tp* tp)" << std::endl;
    }

    // 拷贝构造：
    __shared_count(const __shared_count& __r):
    base_(__r.base_)
     {
        //  std::cout << "__shared_count copy" << std::endl;
         base_->add_ref_copy();
     }

     // 拷贝赋值
     __shared_count& operator=(const __shared_count& __r)
     {
        if (&__r != this)          // 证同测试
        {
             _Sp_counted_base* __tmp = __r.base_;
            if (__tmp)
            {
                __tmp->add_ref_copy();
            }
            if (base_)
            {
                base_->release();
            }
            base_ = __tmp;
         }
         return *this;
     }

     ~__shared_count()
     {
         if (base_)
         {
            base_->release();    
         }
     }

     unsigned int get_use_count() const { return base_ ? base_->get_use_count(): 0; }

private:
    _Sp_counted_base* base_;
};

/*************************************************************
 * 对外，提供接口
 * ***********************************************************/
template<typename _Tp> class __shared_ptr_access;

template<typename _Tp>
class shared_ptr:  public __shared_ptr_access<_Tp>
{
public:
    typedef _Tp element_type;

    shared_ptr(): ptr_(nullptr), refcount_() {}

    template<typename _Yp>              // TODO 需要判断_Yp*转换为_Tp是否合法
    shared_ptr(_Yp* __p):
    ptr_(__p),
    refcount_(__p)
    {
        // std::cout << "shared_ptr::template<typename _Yp> shared_ptr(_Yp* __p)" << std::endl;
    }

    // 拷贝构造
    shared_ptr(const shared_ptr& __r):           // stl中为什么是default
    ptr_(__r.ptr_),
    refcount_(__r.refcount_)             // refcount是私有变量，用对象为什么能访问？
    {
        // std::cout << "shared_ptr copy constructor" << std::endl;
    }

    template<typename _Yp>
    shared_ptr(const shared_ptr<_Yp>& __r):
    ptr_(__r.ptr_),
    refcount_(__r.refcount_)
    {
        // std::cout << "shared_ptr copy constructor2" << std::endl;
     }

    // 拷贝赋值运算符
    shared_ptr& operator=(const shared_ptr& __r)
    {
        ptr_ = __r.ptr_;
        refcount_ = __r.refcount_;
        return *this;
    }

    ~shared_ptr()
    {
        // std::cout << "~shared_ptr" << std::endl;
    }

    operator bool() const
    {
        return ptr_ != nullptr;
    }

    unsigned int use_count() const
    {
        return refcount_.get_use_count();
    }

    bool unique() const
    {
        return use_count() ? true: false;
    }

    shared_ptr* swap(shared_ptr& __r)
    {
        retrun this;
    }

public:
    element_type* get()
    {
        return ptr_;
    }

private:
    element_type* ptr_;
    __shared_count refcount_;
};

/***************************************************************
 * 负责对指针的访问
 * *************************************************************/
template<typename _Tp>
class __shared_ptr_access
{
public:
    typedef _Tp element_type;

    // 内建类型就不能有这个方法，怎么避免？TODO
    element_type* operator->()
    {
        return static_cast<shared_ptr<_Tp>*>(this)->get();
    }

    element_type& operator*()           // 必须是一个引用吗？
    {
        return *(static_cast<shared_ptr<_Tp>*>(this)->get());
    }

};


} // namespace gNet

#endif
