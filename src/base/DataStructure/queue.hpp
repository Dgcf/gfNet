#include <deque>
#include <vector>
#include <functional>
#include <algorithm>
#include <string.h>
using namespace std;

namespace gNet
{

template<typename _Tp, typename _Sequence>
class queue
{
public:
    typedef typename _Sequence::value_type value_type;
    typedef typename _Sequence::reference reference;
    typedef typename _Sequence::const_reference const_reference;
    typedef typename _Sequence::size_type size_type;
    typedef _Sequence container_type;

public:
    // 构造函数需要支持哪些
    explicit queue(value_type __x): c(__x)
    {
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

    reference front() const             // 需要const_reference吗
    {
        assert(!c.empty());
        return c.front();
    }

    reference back() const
    {
        assert(!c.empty());
        return c.back();
    }

    void pop()
    {
        assert(!c.empty());
        c.pop_front();
    }

    void push(const value_type& __x)
    {
        c.push_back(__x);
    }

#if __cplusplus>=201103L
    void push(value_type&& __x)
    {
        c.push_back(std::move(__x));
    }
#endif


private:
    _Sequence c;
};

/***********************************************
 * 优先级队列
 * *********************************************/
template<typename _Tp, typename _Sequence=vector<_Tp>, typename _Pr=std::less<typename _Sequence::value_type>>
class priority_queue
{
public:
    typedef typename _Sequence::value_type value_type;
    typedef typename _Sequence::size_type size_type;
    typedef typename _Sequence::reference reference;
    typedef typename _Sequence::const_reference const_reference;
    typedef _Sequence container_type;
	typedef _Pr value_compare;

public:
	void push(const _Tp& __x)
	{
		c_.push_back(__x);
		push_heap(c_.begin(), c_.end(), comp_);
	}

#if _cplusplus>=201103L
	void push(value_type&& __val)
	{
		c.push_back(std::move(__val));
		push_heap(c.begin(), c.end(), comp_);
	}
#endif

	void pop()
	{
		pop_heap(c_.begin, c_.end, comp_);
		c_.pop_back();
	}

	reference top() const
	{
		return c_.front();
	}

	bool empty() const
	{
		return c_.empty();
	}

	size_type size() const
	{
		return c.size();
	}

private:
	container_type c_;
	value_compare comp_;
};

// 循环队列 数组实现
template<typename _Tp, unsigned int elemSize>
struct sqQueue
{
    sqQueue(): front_(nullptr), rear_(nullptr)
    {
        memset(data_, 0, sizeof(data_));
    }

    _Tp data_[elemSize];
    unsigned int front_;
    unsigned int rear_;
};

template<typename _Tp, unsigned int elemSize>
class stack_loop
{
public:
    stack_loop() {}
    unsigned int size() const
    {
        return (queue_.rear_-queue_.front_+elemSize) % elemSize;
    }

    void push(const _Tp& __Val)
    {
        if(size() + 1 == elemSize)
        {
            return;
        }
        *queue_.rear_ = __Val;
        
    }

private:
    sqQueue<_Tp, elemSize> queue_;
};

}

