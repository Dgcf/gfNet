#ifndef GFNET_LIST_H_
#define GFNET_LIST_H_

namespace gNet
{

template<typename _T>
struct _list_node
{
    typedef void* void_pointer;
    void_pointer prev;
    void_pointer next;
};

template<typename _Tp>
class _List_iterator
{
    typedef ptrdiff_t       difference_type;
    typedef _Tp                 value_type;
    typedef _Tp*               pointer;
    typedef _Tp&              reference;

    
};

template<typename _Ty>
class list
{

};

} // namespace gNet

#endif
