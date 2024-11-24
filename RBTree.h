#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <map>
using namespace std;
enum Colour
{
	RED,
	BLACK
};

template<class K, class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	std::pair<K, V> _kv;
	Colour _col;
	RBTreeNode(const pair<K, V>& _kv)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(_kv)
		, _col(RED)
	{}
};

template<class K,class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:

	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(kv);
		cur->_col = RED; //����Ϊ��ɫ�ڵ㣬������ɫ��ֱ�Ӵ��ƹ���--ÿ��·���ĺ�ɫ�ڵ�������ͬ
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
		}
		else {
			parent->_left = cur;
		}
		cur->_parent = parent;
		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_left)
					{
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						RotateL(parent);
						RotateR(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
			else
			{
				Node* uncle = grandfather->_left;
				if (parent == grandfather->_right)
				{
					//��Ҫ������
					Node* uncle = grandfather->_left;
					if (uncle && uncle->_col == RED)
					{
						parent->_col = uncle->_col =  BLACK;
						grandfather->_col = RED;
						cur = grandfather;
						parent = cur->_parent;
					}
					else
					{
						//���岻���ڻ���Ϊ�ڲ��漰����ת��
						if (cur == parent->_right)
						{
							RotateL(grandfather);
							parent->_col = BLACK;
							grandfather->_col = RED;
						}
						else
						{
							RotateR(parent);
							RotateL(grandfather);
							cur->_col = BLACK;
							grandfather->_col = RED;
						}
						break;
					}
				}
			}
		}
		_root->_col = BLACK;
		return true;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;
		subL->_right = parent;

		Node* ppNode = parent->_parent;
		parent->_parent = subL;
		if (parent == _root) {
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent) {
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}
			subL->_parent = ppNode;
		}
		
	}


	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		subR->_left = parent;

		Node* ppNode = parent->_parent;
		parent->_parent = subR;
		if (parent == _root) {
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent) {
				ppNode->_left = subR;
			}
			else
			{
				ppNode->_right = subR;
			}
			subR->_parent = ppNode;

		}
	

	}
	void InOrder() {
		_InOrder(_root);
	}

	bool Isbalance()
	{
		if (_root->_col == RED)
		{
			return false;
		}
		int refNum = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
			{
				refNum++;

			}
			cur = cur->_left;
		}

		return Check(_root,0,refNum);
	}
private:
	bool Check(Node* root,int blackNum,const int refNum)
	{
		if (root == nullptr)
		{
			if (blackNum != refNum)
			{
				return false;
			}
			return true;
		}
		if (root->_col == RED && root->_parent->_col == RED)
		{
			cout << root->_kv.first << "���������ĺ�ɫ�ڵ�" << endl;
			return false;
		}
		if (root->_col == BLACK)
		{
			blackNum++;
		}
		return Check(root->_left, blackNum, refNum) && Check(root->_right, blackNum, refNum);

	}
	void _InOrder(Node* root)
	{
		if (root == nullptr) {
			return;
		}
		_InOrder(root->_left);
		cout << root->_kv.first << " " << root->_kv.second << endl;
		_InOrder(root->_right);
	}
	Node* _root = nullptr;
	size_t size = 0;
};