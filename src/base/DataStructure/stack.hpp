#include <deque>
using namespace std;


namespace gNet
{

template<typename _Tp, typename _Sequence=deque<_Tp>>
class stack
{
public:
    typedef typename _Sequence::value_type value_type;
    typedef typename _Sequence::reference reference;
    typedef typename _Sequence::const_reference const_reference;
    typedef typename _Sequence::size_type size_type;
    typename _Sequence container_type;

public:
    void push(const value_type& __x)
    {
        c.push_back(__x);
    }

#ifdef __cplusplus>=201103L
    void push(value_type&& __x)
    {
        c.push_back(std::move(__x));        // ?
    }
#endif

    void pop()
    {
        assert(!c.empty());
        c.pop_back();
    }

    reference top() const       // 这里返回引用是否合适；是否需要返回const_reference类型？
    {
        assert(!c.empty());
        return c.back();
    }

    bool empty() const
    {
        return c.empty();
    }

    size_type size() const
    {
        return c.size();
    }

    void clear()
    {
        c.clear();
    }

private:
    _Sequence c;
};

/******************************************************
 * 栈的顺序存储结构
 * ****************************************************/
template<typename _Tp, int elemSize>
struct SqStack
{
    _Tp data_[elemSize];
    int top_;
};

template<typename _Tp, int elemSize>
class stack_array
{
public:
    void push(const _Tp& __Val)
    {
        assert(++sq_.top_<elemSize);
        sq_.data_[sq_.top_] = elemSize;
    }

    _Tp pop()
    {
        _Tp tmp = sq_.data_[sq_.top_];
        sq_.data_[sq_.top_] = 0;
        --sq_.top_;
        return tmp;
    }

private:
    SqStack<_Tp, elemSize> sq_;
};

/**********************************************************
 * 两栈共享，原理如下：
 * 一个栈的栈底为数组的始端，另一个栈的栈底为数组的末端，
 * 增加元素时两个栈向中间靠拢
 * ********************************************************/
template<typename _Tp, unsigned int elemSize>
struct SqdoubleStack
{
    _Tp data_[elemSize];
    unsigned int top1_;
    unsigned int top2_;
};

template<typename _Tp, unsigned int elemSize>
class 


}

