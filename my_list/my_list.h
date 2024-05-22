#pragma once
#include <assert.h>
#include <iostream>
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



	template <class T, class Ref, class Ptr>
	struct ListIterator
	{
		typedef ListNode<T> Node;
		typedef ListIterator< T, Ref, Ptr> Self;

		Node* _node;

		ListIterator(Node* node)
			:_node(node)
		{}

		

		Ref operator*()
		{
			return _node->_data;
		}

	
		Ptr operator->()
		{
			return &_node->_data;
		}

		Self& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		Self operator++(int)
		{
			Self tmp(*this);
			_node = _node->_next;
			return tmp;
		}

		Self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		

		Self operator--(int)
		{
			Self tmp(*this);
			_node = _node->_prev;
			return tmp;
		}


		

		bool operator==(const Self& it)
		{
			return _node == it._node;
		}

		bool operator!=(const Self& it)
		{
			return !(*this == it);
		}
	};




	//template<class T>
	//struct ListConstIterator
	//{
	//	typedef ListNode<T> Node;
	//	typedef ListConstIterator<T> Self;

	//	Node* _node;

	//	ListConstIterator(Node* node)
	//		:_node(node)
	//	{}
	//	//其实const迭代器和普通迭代器的区别就在于解引用
	//const T& operator*()
	//	{
	//		return _node->_data;
	//	}

	//const T* operator->()
	//	{
	//		return &_node->_data;
	//	}

	//	Self& operator++()
	//	{
	//		_node = _node->_next;
	//		return *this;
	//	}

	//	Self& operator--()
	//	{
	//		_node = _node->prev;
	//		return *this;
	//	}

	//	Slef operator++(int)
	//	{
	//		Self tmp(*this);
	//		_node = _node->_next;
	//		return tmp;
	//	}

	//	Self operator--(int)
	//	{
	//		Self tmp(*this);
	//		_node = _node->prev;
	//		return tmp;
	//	}




	//	bool operator==(const Self& it)
	//	{
	//		return _node == it._node;
	//	}

	//	bool operator!=(const Self& it)
	//	{
	//		return !(*this == it);
	//	}
	//};



	template<class T>
	class list
	{
		typedef ListNode<T> Node;
		
	public:
		typedef ListIterator<T, T&, T*> iterator;
		typedef ListIterator<T, const T&, const T*> const_iterator;
		iterator begin()
		{
			return _head->_next;
		}

		const_iterator begin() const
		{
			return _head->_next;
		}

		iterator end()
		{
			return _head;
		}


		const_iterator end() const
		{
			return _head;
		}

		void empty_init()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
			_size = 0;
		}

		list()
		{
			empty_init();
		}


		list(const list<T>& lt)
		{
			empty_init();
			for (auto& e : lt)
			{
				push_back(e);
			}
		}


		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it); //防止迭代器失效，返回下一个位置
			}
		}

		void swap(list<T>& lt)
		{
			std::swap(_head, lt._head);
			std::swap(_size, lt._size);
		}

		list<T>& operator=(list<T> lt)
		{
			swap(lt);
			return *this;
		}

		/*void push_back(const T& x)
		{
			Node* newnode = new Node(x);
			Node* tail = _head->_prev;

			tail->_next = newnode;
			newnode->_prev = tail;
			newnode->_next = _head;
			_head->_prev = newnode;
		}*/

		void push_back(const T& x)
		{
			insert(end(), x);
		}


		void push_front(const T& x)
		{
			insert(begin(), x);
		}


		void pop_back()
		{
			erase(--end());
		}



		void pop_front()
		{
			erase(begin());
		}


		iterator insert(iterator pos, const T& val)
		{
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* newnode = new Node(val);

			prev->_next = newnode;
			newnode->_next = cur;
			newnode->_prev = prev;
			cur->_prev = newnode;
			_size++;

			return newnode;
		}


		iterator erase(iterator pos)
		{
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;

			prev->_next = next;
			next->_prev = prev;
			delete cur;
			_size--;
			return next;  //隐式类型转换
		}


		size_t size() const
		{
			return _size;
		}



		bool empty()
		{
			return _size == 0;
		}
	private:
		Node* _head;
		size_t _size;
	};

	void test_list1()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);
		list<int>::iterator it = lt.begin();
		while (it != lt.end())
		{
			*it += 10;
			std::cout << *it << " ";
			++it;
		}
		std::cout << std::endl;
	}



	void test_list2()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);
		
		lt.erase(lt.begin());
		list<int>::iterator it = lt.begin();
		while (it != lt.end())
		{
			std::cout << *it << " ";
			++it;
		}
		std::cout << std::endl;
	}
}

