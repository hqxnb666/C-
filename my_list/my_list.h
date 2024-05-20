#pragma once
#include <assert.h>

namespace bit
{
	template <class T>
	struct ListNode
	{
		ListNode<T>* _next;
		ListNode<T>* _prev;

		T _data;

		ListNode(const T& x = T())
			:_next(nullptr)
			,_prev(nullptr)
			,_data(x)
		{}
	};

	template<class T>
	class list
	{
	
		typedef ListNode<T> Node;
	public:
		void push_back(const T& x)
		{
			Node* newnode = new Node(x);
			Node* tail = _head->_prev;

			tail->_next = newnode;
			newnode->_prev = tail;
			newnode->_next = _head;
			_head->_prev = newnode;
		}
	private:
		Node* _head;
	};
}