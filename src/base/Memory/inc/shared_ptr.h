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
    _Sp_counted_base(int count):
    use_count_(count)
    {
        std::cout << use_count_ << std::endl;
    }

    // 拷贝构造：
    _Sp_counted_base( _Sp_counted_base& lb)
    {
        ++use_count_;
        --lb.use_count_;
    }

    void add_ref_lock()
    {
        __sync_fetch_and_add(&use_count_, 1);
        // __atomic_fetch_add(&use_count_, 2); 这个系列的函数在哪查找？
    }

    void minus_ref_lock();

    virtual ~_Sp_counted_base()
    {
        std::cout << --use_count_ << std::endl;
        std::cout << "~_Sp_counted_base" << std::endl;
    }

    unsigned int getcount() { return use_count_; }

private:
    unsigned int use_count_;
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
    _Sp_counted_ptr(_Ptr* ptr): _Sp_counted_base(1),
    ptr_(ptr)
    {
    }

    // 拷贝构造：
    _Sp_counted_ptr( _Sp_counted_ptr& lptr):
    _Sp_counted_base(lptr),
    ptr_(lptr.ptr_)
    {
    }

    ~_Sp_counted_ptr()
    {
        std::cout << "~_Sp_counted_ptr" << std::endl;
        if (getcount() == 0)
        {
            dispose();    
        }
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
        std::cout << "template<typename _Tp>__shared_count(_Tp* tp)" << std::endl;
    }

    // 拷贝构造：
    __shared_count( __shared_count& lsh):
    base_(lsh.base_)
     {
     }

     ~__shared_count()
     {
        if (base_)
         {
             delete base_;
         }
         
        std::cout << "~__shared_count" << std::endl;
     }

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
    refcount_(__p)
    {
        std::cout << "shared_ptr::template<typename _Yp> shared_ptr(_Yp* __p)" << std::endl;
    }

    // 拷贝构造
    shared_ptr(shared_ptr& lp):
    ptr_(lp.ptr_),
    refcount_(lp.refcount_)
    {
    }

    template<typename _Yp>
    shared_ptr(const shared_ptr<_Yp>& lptr):
    ptr_(lptr.ptr_),
    refcount_(lptr.refcount_)
    { }

    // 拷贝赋值运算符
    shared_ptr& operator=(const shared_ptr& lptr)
    {
        // ptr_ = lptr.ptr_;
        return *this;
    }

    ~shared_ptr()
    {
        std::cout << "~shared_ptr" << std::endl;
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
    element_type* operator->()
    {
        return static_cast<shared_ptr<_Tp>*>(this)->get();
    }

    element_type& operator*()           // 必须是一个引用吗？
    {
        return *(dynamic_cast<shared_ptr<_Tp>*>(this)->get());
    }

};


} // namespace gNet

#endif
