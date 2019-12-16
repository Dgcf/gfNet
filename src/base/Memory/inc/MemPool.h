#ifndef GFNET_MEMPOOL_H
#define GFNET_MEMPOOL_H

#include <iostream>
using namespace std;
namespace gNet
{

struct default_user_allocator
{
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
};

// 指针类型一律使用char*
template<typename _Ty>
class PODPtr
{
public:
    typedef _Ty  size_type;
private:
    char* ptr;
    size_type     sz;

public:
    PODPtr(char* p, _Ty n): ptr(p), sz(n)
    {}

    PODPtr(): ptr(nullptr), sz(0)
    {}

    ~PODPtr(){}

private:
public:
    // 存放nextsize和nextptr的大小是多少？
    char* ptr_next_size() const { return ptr + sz - sizeof(size_type); }            // 这里是sizeof(size_type)而不是sizeof(char*)

    char* ptr_next_ptr() const { return ptr_next_size() - sizeof(char*); }

public:
    char* begin() const { return ptr; }
    char* & begin() { return ptr; }
    char* end() const { return ptr_next_ptr(); }

    // 判断ptr是否有效
    bool valid() const { return ptr != nullptr; }

    // 使内存无效
    bool invalid() { begin() = nullptr; }

    // 总的大小
    size_type total_size() const { return sz; }

    // 有效数据区（除去两个区域）
    size_type element_size() const { return sz - sizeof(char*) - sizeof(size_type); }

    // 不改变指针，修改指针指向的内容
    size_type& next_size() const { return *(static_cast<size_type*>(static_cast<void*>(ptr_next_size()))); }

    // 返回指向下一个内存的指针(返回的是最后一个)
    char*& next_ptr()  const { return *(static_cast<char**>(static_cast<void*>(ptr_next_ptr()))); }

    void next(const PODPtr<size_type>& arg)
    {
        next_ptr() = arg.begin();
        next_size() = arg.total_size();
    }

    PODPtr<size_type> next() const { return PODPtr<size_type>(next_ptr(), next_size()); }
};

// 指针类型一律使用void*
template<typename SizeType>
class simple_segregated_storage
{
public:
    typedef SizeType size_type;

protected:
    void* first;                // 也是void*, 总是指向第一个空的内存区域；核心
    simple_segregated_storage(): 
    first(nullptr) 
    { }

protected:
    void*& nextof(void *const ptr)
    {
        return *static_cast<void**>(ptr);
    }

public:
    bool empty() const { return first == nullptr; }

    void* malloc() 
    {
        void *const ret = first;
        first = nextof(first);
        return ret; 
    }

    void free(char* const chunk)
    {
        nextof(chunk) = first;
        first = chunk;
    }

    void* add_block(void* begin, unsigned int len, unsigned int partionsize)
    {
        unsigned int num = len / partionsize;
        char* old = static_cast<char*>(begin) + (num - 1) * partionsize;
        nextof(old) = first;        // 尾端指向为空

        for (char*  iter = old-partionsize; iter != begin; old=iter, iter-=partionsize)
        {
            nextof(iter) = old;
        }
        nextof(begin) = old;

        first = begin;
        return malloc();
    }
};

template<typename UserAllocator>
class pool: public simple_segregated_storage<typename UserAllocator::size_type>
{
public:
    typedef UserAllocator user_allocator;
    typedef typename UserAllocator::size_type size_type;

    pool(int size, int num): 
    chunk_size(size), 
    chunk_num(num), 
    list_(0, 0),
    malloc_num(0),
    free_num(0),
    x(0)
    { }

    ~pool() 
    {
        PODPtr<size_type> prev = list_;
        do
        {
            PODPtr<size_type> next = prev.next();
            delete[] prev.begin();
            prev = next; 
        } while (prev.valid());
    }

protected:
    simple_segregated_storage<size_type>* store() { return dynamic_cast<simple_segregated_storage<size_type>*>(this); }
    void* malloc_need_resize()
    {
        // 暂时未考虑内存对齐
        unsigned int alloc_size = chunk_num*chunk_size + sizeof(char*) + sizeof(size_type);
        ptr = new char[alloc_size];
        if (ptr)
        {
            //printf("new memory: %p, size is: %d\n", ptr, alloc_size);
        }
        PODPtr<size_type> node(ptr, alloc_size);
        // 新增的node放到链表最前面
        node.next(list_);
        list_ = node;                // 不断更新list方便下次申请的链接
                                                 // list每次是最新的
        if (++x == 3)
        {
            PODPtr<size_type> t = list_.next();
            t = t.next();
            printf("t: %p\n", t.begin());
        }
        return  store()->add_block(node.begin(), node.element_size(), chunk_size);
    }

    void check_list()
    {
        PODPtr<size_type> prev = list_;
        while (prev.valid())
        {
            printf("--------------------list_.begin is %p\n", prev.begin());
            prev = prev.next();
        }
    }

public:
    int x;
    void* malloc()
    {
        if (store()->empty())
        {
            return malloc_need_resize();
        }
        return store()->malloc();       // 这个对象不能调用protected成员
    }

    void free(char* const chunk)
    {
        store()->free(chunk);
    }

private:
    //std::vector<PODPtr<size_type>> v_;
    PODPtr<size_type> list_;
    char* ptr;
    int chunk_size;
    int chunk_num;
    int malloc_num;
    int free_num;
};

}

#endif
