#include <deque>
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
template<typename _Tp, typename _Sequence>
class priority_queue
{
public:
    typedef typename _Sequence::value_type value_type;
    typedef typename _Sequence::size_type size_type;
    typedef typename _Sequence::reference reference;
    typedef typename _Sequence::const_reference const_reference;
    typedef _Sequence container_type;


};


}
