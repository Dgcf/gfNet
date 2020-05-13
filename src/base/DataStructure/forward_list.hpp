namespace gnet
{

template<typename _Tp>
class Node
{
public:
    Node(const _Tp& __val, Node<_Tp>* __p=nullptr):
    value_(__val), next_(__p)
    {}

    _Tp value_;
    Node<_Tp> *next_;
};

/**********************************************************
 * 单链表
 * ********************************************************/
template<typename _Tp>
class forward_list
{
public:

/******************************************
 * 构造
 * ****************************************/
    forward_list(const _Tp& __v):
    first_(new Node<_Tp>(__v))
    {
    }

// 非更易性操作
    bool empty() const
    {
        return first_==nullptr;
    }

    /**************************************
     * 在第i个元素之前插入元素__val
     * ************************************/
    void insert(unsigned int i, const _Tp& __val)
    {
        if (!first_)
        {
            first_ = new Node<_Tp>(__val);
            return;
        }
        if(i==0)
        {
            Node<_Tp> *head = new Node<_Tp>(__val, first_);
            first_ = head;
        }
        
        Node<_Tp> *tmp = first_->next_, *pre = first_;
        int index = 0;
        while (pre)
        {
            if (++index == i)
            {
                pre->next_ = new Node<_Tp>(__val);
                pre->next_->next_ = tmp;
            }
            pre = pre->next_;
            tmp = tmp->next_;
        }
    }

    // 整表删除
    void clear()
    {
        Node<_Tp> *tmp = nullptr;
        while (first_)
        {
            tmp = first_;
            first_ = first_->next_;
            delete tmp;
        }
    }

    // 读取下标为index的元素,复杂度为O(n)
    _Tp operator[](unsigned int index)
    {
        int i = 0;
        Node<_Tp> *tmp = first_;
        while (tmp)
        {
            if (i++ == index)
            {
                return tmp->value_;
            }
            tmp = tmp->next_;
        }
    }

// 遍历打印出所有元素
    void print() const
    {
        Node<_Tp> *tmp = first_;
        while (tmp)
        {
            std::cout << tmp->value_ << "\n";
            tmp = tmp->next_;
        }
        std::cout << std::endl;
    }

private:
    Node<_Tp> *first_, end_;
};

}
