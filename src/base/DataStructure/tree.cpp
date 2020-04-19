#include <queue>
#include <stack>
using namespace std;

namespace gnet
{

template<typename _Tp>
class BSTNode
{
public:
	BSTNode(const _Tp& __Val, BSTNode<_Tp> *__l=nullptr, BSTNode<_Tp> *__r=nullptr):
	elem_(__Val),
	left_(__l),
	right_(__r)
	{}

	_Tp elem_;
	BSTNode<_Tp> *left_, *right_;

};

template<typename _Tp>
class BST
{
public:
	BST():root_(nullptr) {}

	bool empty() const
	{
		return root_==nullptr;
	}

	// 查找
	_Tp* search(BSTNode<_Tp>* p, const _Tp& el) const
	{
		while(p)
		{
			if(p->elem_ == el)
			{
				return &p->elem_;
			}
			else if(p->elem_ > el)
			{
				p = p->left_;
			}
			else
			{
				p = p->right_;
			}
		}
	}

	// 广度优先遍历
	void breadthFirst()
	{
		std::queue<BSTNode<_Tp>*> que;
		BSTNode<_Tp> *p = root_;
		if (p)
		{
			que.push(p);
			while (!que.empty())
			{
				p = que.pop();		// 需要删除首元素
				visit(p);
				if(p->left_)
				{
					que.push(p->left_);
				}
				if(p->right_)
				{
					que.push(p->right_);
				}
			}
		}
	}
	// 深度优先遍历
	// 1.中序数遍历
	void inorder(BSTNode<_Tp>* p)
	{
		if(p != 0)
		{
			inorder(p->left_);
			visit(p);
			inorder(p->right_);
		}
	}

	// 2.前序数遍历
	void preorder(BSTNode<T>* p)
	{
		if(p)
		{
			visit(p);
			preorder(p->left_);
			preorder(p->right_);
		}
	}

	// 3.后序数遍历
	void postorder(BSTNode<T>* p)
	{
		if(p)
		{
			postorder(p->left_);
			postorder(p->right_);
			visit(p);
		}
	}

	// 非递归版本的实现

	// 插入算法
	void insert(const _Tp& __val)
	{
		BSTNode<_Tp> *p = root, *prev = nullptr;
		while (p)
		{
			/* code */
		}
		
	}

private:
	void visit(BSTNode<_Tp>* p)
	{
		cout << p->elem_;
	}

private:
	BSTNode<_Tp>* root_;
};

// 通用线索树及其中序遍历的实现
template<typename T>
class ThreadedNode
{
public:

};

}
