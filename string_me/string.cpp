#define _CRT_SECURE_NO_WARNINGS
#include "my_string.h"


namespace my_string {
	const int string::npos = -1;
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

	 void string::reserve(size_t n)
	 {
		 if (n > _capacity)
		 {
			 char* tmp = new char[n + 1];
			 strcpy(tmp, _str);
			 delete[]_str;
			 _str = tmp;
			 _capacity = n;
		 }
	 }
	 void string::pushback(char ch)
	 {
		 if (_size == _capacity)
		 {
			 reserve(_capacity == 0 ? 4 : 2 * _capacity);
		 }
		 _str[_size] = ch;
		 _size++;
		 _str[_size] = '\0';
	 }
	 void string::append(const char* str)
	 {
		 size_t len = strlen(str);
		 if (_size + len > _capacity)
		 {
			 reserve(_size + len);
		 }
		 strcpy(_str + _size, str);
		 _size += len;
		
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
	size_t string::find(char ch, size_t pos ) const
	{
		assert(pos < _size);
		for (size_t i = pos	; i < _size; i++)
		{
			if (_str[i] == ch)
			{
				return i;
			}
		}
		return npos;
	}
	size_t string::find(char* sub, size_t pos )const
	{
		assert(pos < _size);
		const char* p = strstr(_str + pos, sub);
		if (p)
		{
			return p - _str;
		}
		else
		{
			return npos;
		}
	}
	size_t string::size()const
	{
		return _size;
	}
	size_t string::capacity()const
	{
		return _capacity;
	}
	void string::insert(size_t pos, char ch)
	{
		assert(pos <= _size);
			if (_size == _capacity)
			{
				reserve(_capacity == 0 ? 4 : 2 * _capacity);
			}
		int end = _size + 1;
		while (end > pos)
		{
			_str[end--] = _str[end - 1];
		}
		_str[end] = ch;
		_size++;

	}
	void string::earse(size_t pos, size_t len )
	{
		assert(pos < _size);
		if (len == npos || len >= _size - pos)
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
	void string::insert(size_t pos, const char* str)
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
			_str[end - 1 + len] = _str[end - 1];
			--end;
		}
		strncpy(_str + pos, str, len);
		_size += len;
	}
	void string::resize(size_t n, char ch )
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
				_str[i++] = ch;
			}
			_str[n] = '\0';
			_size = n;
		}
	}
	string& string::operator+=(char ch)
	{
		pushback(ch);
		return *this;
	}
	string& string::operator+=(const char* str)
	{
		//要先实现pushback 和  append
		append(str);
		return *this;
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
	bool string::empty()const
	{
		return _str == nullptr ? false : true;
	}
}