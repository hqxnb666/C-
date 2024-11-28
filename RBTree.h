#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <iostream>
using namespace std;

enum Colour
{
    RED,
    BLACK
};

template<class T>
struct RBTreeNode
{
    RBTreeNode<T>* _left;
    RBTreeNode<T>* _right;
    RBTreeNode<T>* _parent;
    T _data;
    Colour _col;
    RBTreeNode(const T& data)
        : _left(nullptr)
        , _right(nullptr)
        , _parent(nullptr)
        , _data(data)
        , _col(RED)
    {}
};

template<class T, class Ref, class Ptr>
struct __RBtreeIterator
{
    typedef RBTreeNode<T> Node;
    typedef __RBtreeIterator<T, Ref, Ptr> Self;
    Node* _node;
    __RBtreeIterator(Node* node)
        : _node(node)
    {}

    Ref operator*() const
    {
        return _node->_data;
    }
    Ptr operator->() const
    {
        return &_node->_data;
    }
    bool operator!=(const Self& s) const
    {
        return _node != s._node;
    }

    // 前置递增
    Self& operator++()
    {
        if (_node->_right)
        {
            Node* leftmin = _node->_right;
            while (leftmin->_left)
            {
                leftmin = leftmin->_left;
            }
            _node = leftmin;
        }
        else
        {
            Node* cur = _node;
            Node* parent = _node->_parent;
            while (parent && cur == parent->_right)
            {
                cur = parent;
                parent = parent->_parent;
            }
            _node = parent;
        }
        return *this;
    }

    // 后置递增
    Self operator++(int)
    {
        Self tmp = *this;
        ++(*this);
        return tmp;
    }
};

template<class K, class T, class KeyofT>
class RBTree
{
    typedef RBTreeNode<T> Node;
public:
    typedef __RBtreeIterator<T, T&, T*> Iterator;
    typedef __RBtreeIterator<T, const T&,const T*> ConstIterator;

    //拷贝构造
    RBTree() = default;
    RBTree(const RBTree< K,  T, KeyofT>& t)
    {
        _root = Copy(t._root);
    }
    ~RBTree()
    {
        Destory(_root);
        _root = nullptr;
    }
    void Destory(Node* root)
    {
        if (root == nullptr)
        {
            return;
        }
        Destory(root->_left);
        Destory(root->_right);
        delete root;
        root = nullptr;
    }

    RBTree<K, T, KeyofT>& operator=(RBTree<K, T, KeyofT> t)
    {
        swap(_root, t._root);
        return *this;
    }
    Node* Copy(Node* root)
    {
        if (root == nullptr)
        {
            return;
        }
        Node* newroot = new Node(root);
        newroot->_col = root->_col;
        newroot->_left = Copy(root->_left);
        if (newroot->_left) {
            newroot->_left->_parent = newroot;
        }
        newroot->_right = Copy(root->_right);
        if (newroot->_right) {
            newroot->_right->_parent = newroot;
        }
        return newroot;
    }
    Iterator Begin()
    {
        Node* leftmin = _root;
        while (leftmin && leftmin->_left)
        {
            leftmin = leftmin->_left;
        }
        return Iterator(leftmin);
    }
    Iterator End()
    {
        return Iterator(nullptr);
    }
    bool Insert(const T& data)
    {
        if (_root == nullptr)
        {
            _root = new Node(data);
            _root->_col = BLACK;
            return true;
        }
        KeyofT kot;
        Node* parent = nullptr;
        Node* cur = _root;
        while (cur)
        {
            K currentKey = kot(cur->_data);
            K newKey = kot(data);
            if (currentKey < newKey)
            {
                parent = cur;
                cur = cur->_right;
            }
            else if (currentKey > newKey)
            {
                parent = cur;
                cur = cur->_left;
            }
            else
            {
                // 键已存在，插入失败
                return false;
            }
        }
        cur = new Node(data);
        cur->_col = RED;
        if (kot(parent->_data) < kot(data))
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
            if (grandfather == nullptr) break; // 防止空指针
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
                if (uncle && uncle->_col == RED)
                {
                    parent->_col = uncle->_col = BLACK;
                    grandfather->_col = RED;
                    cur = grandfather;
                    parent = cur->_parent;
                }
                else
                {
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

    void InOrder() const {
        _InOrder(_root);
        cout << endl;
    }

    bool Isbalance() const
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

        return Check(_root, 0, refNum);
    }

 

private:
    bool Check(Node* root, int blackNum, const int refNum) const
    {
        if (root == nullptr)
        {
            return blackNum == refNum;
        }
        if (root->_col == RED && root->_parent && root->_parent->_col == RED)
        {
            cout << root->_data.first << " 存在连续的红色节点" << endl;
            return false;
        }
        if (root->_col == BLACK)
        {
            blackNum++;
        }
        return Check(root->_left, blackNum, refNum) && Check(root->_right, blackNum, refNum);
    }

    void _InOrder(Node* root) const
    {
        if (root == nullptr) {
            return;
        }
        _InOrder(root->_left);
        cout << root->_data.first << ":" << root->_data.second << " ";
        _InOrder(root->_right);
    }

    void _destroy(Node* node)
    {
        if (node)
        {
            _destroy(node->_left);
            _destroy(node->_right);
            delete node;
        }
    }

    Node* _root = nullptr;
};
