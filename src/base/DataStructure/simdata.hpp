#include <iostream>
using namespace std;

namespace simdata
{

// 单向链表
template<typename _Ty>
class Node
{
public:
    explicit Node(const _Ty& _v):
    value_(_v),
    next_(nullptr)
    {}

    Node(const _Ty& _v, Node* _n):
    value_(_v),
    next_(_n)
    {}

    _Ty value_;
    Node* next_;
};

// 在任何位置添加或删除速度都很快
template<typename _Dy>
class forward_list
{
public:
    forward_list(const _Dy& _v, Node<_Dy>* _n=nullptr):
    head_(new Node<_Dy>(_v, _n)),
    cur_(head_)
    {}

    // 头部添加
    void AddToHead(const _Dy& _v)
    {
        Node<_Dy>* temp = new Node<_Dy>(_v, head_);
        head_ = temp;
    }

    // 尾部添加
    void AddToTail(const _Dy& _v)
    {
        cur_->next_ = new Node<_Dy>(_v);
        cur_ = cur_->next_;
    }

    // 头部删除
    void DeleteFromHead()
    {
        Node<_Dy>* temp = head_;
        head_ = head_->next_;
        delete temp;
    }

    // 尾部删除
    void DeleteFromTail()
    {
        Node<_Dy>* temp = head_;
        for (; temp != nullptr; temp=temp->next_);
        delete cur_;
        cur_ = temp;
    }

    void PrintAll() const
    {
        for (Node<_Dy>* temp = head_; temp != nullptr; temp=temp->next_)
        {
            cout << temp->value_ << endl;
        }
    }

private:
    Node<_Dy>* head_;
    Node<_Dy>* cur_;
};

// 双向链表

struct slist{
    int val;
    slist* next;
};

void deleteNode(int x)
{
    slist* li;
    int count = 100;
    slist* tmp = li;
    int index = 0;
    while (tmp && index <x)
    {
        tmp = tmp->next;
        ++index;
    }
    
        
}
}
