#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include<assert.h>
namespace bit {
	class string
	{
	public:

		const char* c_str() const
		{
			return _str;
		}

		//这里我们手搓一个迭代器
		typedef char* iterator;
		typedef const char* const_iterator;
		const_iterator begin() const
		{
			return _str;
		}

		const_iterator end() const
		{
			return _str + _size;
		}
		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}

		/*string()
			:_str(new char[1])
			,_size(0)
			,_capacity(0)
		{
			_str[0] = '\0';
		}*/
		//string(const char* str)  //可是这样写很不好  用了三次strlen   所以尤其是对于这种内置类型
		//	//尽量少用strlen  初始化列表用一次就可以
		//	:_str(new char[strlen(str)+1])
		//	,_size(strlen(str))
		//	,_capacity(strlen(str))
		//{}

		string(const char* str = "") //严格来说加\0有一些画蛇添足 默认就有\0
			:_size(strlen(str))
		{
			_capacity = _size;
			_str = new char[_size + 1];
			strcpy(_str, str);
		}

		/*string(const string& str)
		{
			_str = new char[str._capacity + 1];
			strcpy(_str, str._str);
			_size = str._size;
			_capacity = str._capacity;
		}*/ 
		//还有现代写法

		string(const string& s)
		{
			string tmp(s._str);
			swap(tmp);
		}
		~string() {
			delete[] _str;
			_str = nullptr;
			_size = 0;
			_capacity = 0;
		}

		string& operator=(const string& s)
		{
			char* tmp = new char[s._capacity + 1];
			strcpy(tmp, s._str);
			delete[] _str;
			_str = tmp;
			_size = s._size;
			_capacity = s._capacity;
			return *this;
		}

		//这个也有现代写法

	/*	string& operator=(string tmp)
		{
			swap(tmp);
			return *this;
		}*/
		size_t size() const
		{
			return _size;
		}
		size_t capacity() const
		{
			return _capacity;
		}
		char& operator[](size_t pos)
		{
			assert(pos < _size);  //这就喝酒了  只要在驾驶座上就会报警
			//而C语言传统越界检查是抽查
			return _str[pos];

		}
	const char& operator[](size_t pos) const
		{
			assert(pos < _size);  //这就喝酒了  只要在驾驶座上就会报警
			//而C语言传统越界检查是抽查
			return _str[pos];

		}

	void resize(size_t n, char ch = '\0')
	{
		if (n <= _size)
		{
			_str[n] = '\0';
			_size = n;
		}
		else
		{
			reserve(n);
			for (size_t i = _size; i < n; i++)
			{
				_str[i] = ch;
			}
			_str[n] = '\0';
			_size = n;
		}
	}
	void reserve(size_t n)
	{
		if (n > _capacity)
		{
			char* tmp = new char[n+1];
			strcpy(tmp, _str);
			delete[] _str;
			_str = tmp;

			_capacity = n;
		}
	}
	void push_back(char ch)
	{
		//扩容2
		if (_size == _capacity)
		{
			reserve(_capacity == 0 ? 4 : 2 * _capacity);
		}
		_str[_size] = ch;
		_size++;
		_str[_size] = '\0';
	}
	void append(const char* str)
	{
		//扩容不能随意
		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			reserve(_size + len);
		}
		strcpy(_str + _size, str);
		_size += len;
	}

	string& operator+=(char ch)
	{
		push_back(ch);
		return *this;
	}
	string& operator+=(const char* str)
	{
		append(str);
		return *this;
	}


	void insert(size_t pos, char ch)
	{
		assert(pos <= _size);
		if (_size == _capacity)
		{
			reserve(_capacity == 0 ? 4 : 2 * _capacity);
		}


		//这样头插会死循环 	size_t end = _size;
			//int end = _size;
			//用int也不行 这样end右边是pos，范围小会向范围大的转化    end还是会变成size_t
			/*while (end >= pos)
			{
				_str[end + 1] = _str[end];
				--end;
			}
			_str[pos] = ch;
			++_size;
		}*/
		int end = _size + 1;
		while (end > pos)
		{
			_str[end] = _str[end - 1];
		}

		_str[end] = ch;
		++_size;
	}
	void insert(size_t pos, const char* str)
	{
		assert(pos <= _size);
		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			reserve(_size + len);
		}
		int end = _size + 1;
		while (end > pos)
		{
			_str[end + len-1] = _str[end - 1];
			--end;
		}
		//strcpy(_str + pos, str);
		strncpy(_str + pos, str,len);
		_size += len;
	}

	void erase(size_t pos, size_t len = npos)
	{
		assert(pos < _size);
		if (len == npos ||  len  >= _size - pos) //这里防止溢出 
		{
			_str[pos] = '\0';
			_size = pos;
		}
		else
		{
			strcpy(_str + pos, _str + pos + len);
			_size -= len;
		}
	}

 void swap( string& s) 
	{
		std::swap(_str, s._str);
		std::swap(_size, s._size);
		std::swap(_capacity, s._capacity);
		
	}
	size_t find(char ch, size_t pos = 0) const
	{
		assert(pos < _size);
		for (size_t i = pos; i < _size; i++)
		{
			if (_str[i] == ch) {
				return i;
			}
		}
		return npos;
	}

	size_t find(char* sub, size_t pos = 0) const
	{
		assert(pos < _size);
		const char* p = strstr(_str + pos, sub);
		if (p) {
			return p - _str;
		}
		else
		{
			return npos;
		}
	}

	void clear()
	{
		_size = 0;
		_str[_size] = '\0';
	}
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		public:
			static const int npos;
	};

	void swap( string& s1,  string& s2)
	{
		s1.swap(s2);
	}

	bool operator==(const string& s1, const string& s2)
	{
		int ret = strcmp(s1.c_str(), s2.c_str());
		return ret == 0;
	}

	bool operator<(const string& s1, const string& s2)
	{
		int ret = strcmp(s1.c_str(), s2.c_str());
		return ret < 0;
	}

	bool operator<=(const string& s1, const string& s2)
	{
		return s1 < s2 || s1 == s2;
	}
	bool operator>(const string& s1, const string& s2)
	{
		return !(s1 <= s2);
	}


	bool operator>=(const string& s1, const string& s2)
	{
		return !(s1 < s2);
	}


	bool operator!=(const string& s1, const string& s2)
	{
		return !(s1 == s2);
	}

	std::ostream& operator<<(std::ostream& out, const string& s)
	{
		for (auto ch : s)
		{
			out << ch;
		}
		return out;
	}

	std::istream& operator>>(std::istream& in, string s)
	{
		s.clear();
		char ch;
		//in >> ch;  //不能用下标 还没开孔加呢
		// 
		ch = in.get();
		char buff[128];
		size_t i = 0;

		//cin 和 scanf读不到空格
		//C语言用getchar 
		while (ch != ' ' && ch != '\n')
		{
			buff[i++] = ch;
			if (i == 127)
			{
				buff[127] = '\0';
				s += buff;
				i = 0;
			}
			ch = in.get();
		}

		if (i > 0)
		{
			buff[i] = '\0';
			s += buff;
		}
		return in;
	}


	std::istream& getline(std::istream& is, string s)
	{
		s.clear();
		char ch;
		//in >> ch;  //不能用下标 还没开孔加呢
		// 
		ch = is.get();

		//cin 和 scanf读不到空格
		//C语言用getchar 
		while ( ch != '\n')
		{
			s += ch;
			ch = is.get();
		}
		return is;
	}

	const int string::npos = -1;
	void test_string1()
	{
		string s1("hello word");
		string s2;
		for (size_t i = 0; i < s1.size(); i++)
		{
			std::cout << s1[i] << " ";
		}
		std::cout << std::endl;
	}
	void test_string2()
	{
		string s3("hello world");
		string::iterator it3 = s3.begin();
		while (it3 != s3.end())
		{
		//	*it3 -= 3;
			std::cout << *it3 << std::endl;
			++it3;
		}
		std::cout << std::endl;


		for (auto ch : s3)
		{
			std::cout << ch << " ";
		}
		std::cout <<  std::endl;
	}

	void test_string3()
	{
		string s1("hello word");
		s1.push_back('1');
		s1.push_back('2');
		std::cout << s1.end() << std::endl;

		string s2("hello word");
		s2.resize(20, 'f');
		std::cout << s2.end() << std::endl;
		string s4(s1);
	}
	void test_string4()
	{
		string s1("hello word");
		
		s1.insert(2,"xxx");
		for (auto ch : s1) {
			std::cout << ch << " ";
		}
		std::cout << std::endl;


		std::cout << s1.c_str() << std::endl;
	}

	void test_string5()
	{
		string s1("hello word");
		string s2("xxx");
		s1 = s2;
		std::cout << s1 << std::endl;
	}
}