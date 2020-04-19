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

}

