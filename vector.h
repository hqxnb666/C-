#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
namespace bit
{
	template <class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		iterator begin();

		iterator end();

		const_iterator begin() const;

		const_iterator end() const;
		vector()
		{};
		size_t size() const;
		size_t capacity() const;
		//��������
		vector(const vector<T>& v);
		//����
		~vector();
		//����
		void reserve(size_t n);
	private:
		iterator _start = nullptr;
		iterator _finish = nullptr;
		iterator _endofstorage = nullptr;
	};

	template<class T>

	typename vector<T>::iterator  vector<T>::begin()
	{
		return _start;
	}

	template<class T>

	typename vector<T>::iterator  vector<T>::end()
	{
		return _finish;
	}


	template <class T>

	typename vector<T>::const_iterator vector<T>::begin() const
	{
		return _start;
	}


	template <class T>
	typename vector<T>::const_iterator vector<T>::end() const
	{
		return _finish;
	}

	template <class T>
	size_t vector<T>::size() const
	{
		return _finish - _start;
	}


	template <class T>
	size_t vector<T>::capacity() const
	{
		return _endofstorage - _start;
	}

	template <class T>
	vector<T>::vector(const vector<T>& v)
	{

	}
	template <class T>
	vector<T>::~vector()
	{
		if (_start)
		{
			delete[] _start;
		}
		_start = _finish = _endofstorage = nullptr;
	}



	template <class T>
	void vector<T>::reserve(size_t n)
	{

	}
}
====== =
#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <iostream>
namespace bit
{
	template <class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		iterator begin();

		iterator end();

		const_iterator begin() const;

		const_iterator end() const;

		const T& operator[](size_t pos) const;

		vector()
		{};
		size_t size() const;
		size_t capacity() const;
		//��������
		vector(const vector<T>& v);
		//����
		~vector();
		//����
		void reserve(size_t n);

		void push_back(const T& val);
		void insert(iterator pos, const T& val);
		void earse(iterator pos);
		void popback();
		void resize(size_t n, const T& val = T());
		bool empty();
	private:
		iterator _start = nullptr;
		iterator _finish = nullptr;
		iterator _endofstorage = nullptr;
	};

	template<class T>

	typename vector<T>::iterator  vector<T>::begin()
	{
		return _start;
	}

	template<class T>

	typename vector<T>::iterator  vector<T>::end()
	{
		return _finish;
	}


	template <class T>

	typename vector<T>::const_iterator vector<T>::begin() const
	{
		return _start;
	}


	template <class T>
	typename vector<T>::const_iterator vector<T>::end() const
	{
		return _finish;
	}

	template <class T>
	size_t vector<T>::size() const
	{
		return _finish - _start;
	}


	template <class T>
	size_t vector<T>::capacity() const
	{
		return _endofstorage - _start;
	}

	template <class T>
	vector<T>::vector(const vector<T>& v)
	{
		reserve(v.capacity());
		for (T& e : v)
		{
			push_back(e);
		}
	}
	template <class T>
	vector<T>::~vector()
	{
		if (_start)
		{
			delete[] _start;
		}
		_start = _finish = _endofstorage = nullptr;
	}



	template <class T>
	void vector<T>::reserve(size_t n)
	{
		if (n > capacity())
		{
			size_t old_size = size();
			T* tmp = new T[n];
			memcpy(tmp, _start, size() * sizeof(T));
			delete[] _start;
			_start = tmp;
			_finish = tmp + old_size;
			_endofstorage = tmp + n;
		}
	}

	template <class T>
	void vector<T>::push_back(const T& val)
	{
		insert(end(), val);
	}

	template <class T>
	void vector<T>::popback()
	{
		erase(--end());
	}

	template <class T>
	void vector<T>::insert(iterator pos, const T& val)
	{
		assert(pos >= _start && pos <= _finish);
		if (_finish == _endofstorage)
		{
			size_t len = pos - _start;
			reserve(capacity() == 0 ? 4 : capacity() * 2);
			pos = _start + len;
		}
		iterator it = _finish - 1;
		while (it >= pos)
		{
			*(it + 1) = *it;
			--it;
		}
		*pos = val;
		++_finish;
	}

	template <class T>
	void vector<T>::earse(vector<T>::iterator pos)
	{
		assert(pos >= _start && pos <= _finish);
		auto it = pos + 1;
		while (it < _finish)
		{
			*(it - 1) = *it;
			++it;
		}
		--_finish;
	}

	template <class T>
	const  T& vector<T>::operator[](size_t pos) const
	{
		assert(pos < size());
		return _start[pos];
	}

	template<class T>
	void vector<T>::resize(size_t n, const T& val)
	{
		if (n > size())
		{
			reserve(n);
			while (_finish < _start + n)
			{
				*_finish = val;
				++_finish;
			}
		}
		else
		{
			_finish = _start + n;
		}
	}

	template<class T>
	bool vector<T>::empty()
	{
		return _start == _finish;
	}



	template<class T>
	void print_vector(const vector<T>& v)
	{
		for (auto e : v)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
	}
}