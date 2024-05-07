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
		//¿½±´¹¹Ôì
		vector(const vector<T>& v);
		//Îö¹¹
		~vector();
		//À©ÈÝ
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
