#define _CRT_SECURE_NO_WARNINGS
#include "my_string.h"


namespace my_string {
	const char* string::c_str() const
	{
		return _str;
	}
	string::iterator string::begin()
	{
		return _str;
	}
	string::iterator string::end()
	{
		return _str + _size;
	}
	 string::const_iterator string:: begin() const
	{
		 return _str;
	}
	 string::const_iterator string::end() const
	 {
		 return _str + _size;
	 }
	void string:: swap(string& s)
	{
		std::swap(_str, s._str);
		std::swap(_size, s._size);
		std::swap(_capacity, s._capacity);
	}
	void string::clear()
	{
		_size = 0;
		_str[_size] = '\0';
	}
	string::string(const char* str )
		:_size(strlen(str))
	{
		_capacity = _size ;
		_str = new char[_size + 1];
		strcpy(_str, str);
	}

	/*string::string(const string& str ) 
	{
		_str = new char[str._size + 1];
		strcpy(_str, str._str);
		_size = str._size;
		_capacity = str._capacity;
	}*/
	string::string(const string& str)
	{
		string tmp(str._str);
		swap(tmp);
	}
	string::~string()
	{
		delete[] _str;
		_str = nullptr;
		_size = 0;
		_capacity = 0;
	}
	/*string& string::operator=(const string& s)
	{
		char* tmp = new char[s._size + 1];
		strcpy(tmp, s._str);
		delete[] _str;
		_str = tmp;
		_size = s._size;
		_capacity = s._capacity;
		return *this;
	}*/
	string& string::operator+=(const char* str)
	{
		//要先实现pushback 和  append
	}
	string& string::operator=(string tmp)
	{
		swap(tmp);
		return *this;
	}

	std::ostream& operator<<(std::ostream& out, const string& s)
	{
		for (auto ch : s)
		{
			out << ch;
		}
		return out;
	}
	std::istream& operator>>(std::istream& in, string& s)
	{
		s.clear();
		char ch;
		ch = in.get();
		char buff[128];
		size_t i = 0;
		while (ch != ' ' && ch != '\0')
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
	
}