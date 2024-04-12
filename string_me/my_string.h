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
		void earse(size_t pos, size_t len = npos);
		void insert(size_t pos, char ch);
		void insert(size_t pos, const char* str);
		void swap(string& s);
		void clear();
		void pushback(char ch);
		void append(const char* str);
		void reserve(size_t n);
		void resize(size_t n, char ch = '\0');
		size_t size()const;
		size_t capacity()const;
		size_t find(char ch, size_t pos = 0)const;
		size_t find(char* sub, size_t pos = 0)const;
		string(const char* str = "");
		string(const string& str);
		~string();
		string& operator=(string tmp);
		string& operator+=(const char* str);
		string& operator+=(char ch);
		bool empty()const;
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
	
	
	std::ostream& operator<<(std::ostream& out, const string& s);
	 
	std::istream& operator>>(std::istream& in, string& s);
	 
     inline	bool operator==(const string& s1, const string& s2)
	{
		int ret = strcmp(s1.c_str(), s2.c_str());
		return ret == 0;
	}
	inline bool operator<(const string& s1, const string& s2)
	{
		int ret = strcmp(s1.c_str(), s2.c_str());
		return ret < 0;
	}
	inline bool operator<=(const string& s1, const string& s2)
	{
		int ret = strcmp(s1.c_str(), s2.c_str());
		return ret < 0 || ret == 0;
	}
	inline bool operator>(const string& s1, const string& s2)
	{
		return !(s1 <= s2);
	}
	inline bool operator>=(const string& s1, const string& s2)
	{
		return !(s1 < s2);
	}
	inline bool operator!=(const string& s1, const string& s2)
	{
		return !(s1 == s2);
	}
	inline void test_string4()
	{
		string s1("hello word");

		s1.insert(2, "xxx");
		for (auto ch : s1) {
			std::cout << ch << " ";
		}
		std::cout << std::endl;


		std::cout << s1.c_str() << std::endl;
	}
}

