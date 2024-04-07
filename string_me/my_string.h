#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <string.h>

namespace my_string {
	class string {
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
	public:
		const_iterator begin() const;
		const_iterator end() const;
		iterator begin();
		iterator end();
		const char* c_str() const;
		void swap(string& s);
		void clear();
		string(const char* str = "");
		string(const string& str);
		~string();
		string& operator=(string tmp);
		string& operator+=(const char* str);
		const char& operator[](size_t pos) const
		{
			assert(pos < _size);
			return _str[pos];
		}
	private:
		char* _str = nullptr;
		size_t _size = 0;
		size_t _capacity = 0;
	public:
		static const int npos;
	};
	const int string::npos = -1;
	
	std::ostream& operator<<(std::ostream& out, const string& s);
	 
	std::istream& operator>>(std::istream& in, string& s);
	 
}

