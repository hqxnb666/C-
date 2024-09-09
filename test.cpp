#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	pair<K, V> _kv;

	AVLTreeNode(const pair<K,V>& _kv)
		:_left(nullptr)
		,_right(nullptr)
		,_kv(_kv)
	{}
};

template<class K, class V>
class AVLTree
{

};