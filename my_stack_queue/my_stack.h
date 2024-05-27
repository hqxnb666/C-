#pragma once
#include <vector>
#include <list>

namespace bit {
	template<class T, class container = std::vector<T>> //ÈÝÆ÷µÄÒâË¼
	class stack
	{
	public:
		void push(const T& x)
		{
			_con.push_back(x);
		}

		void pop()
		{
			_con.pop_back();
		}

		size_t size()
		{
			return _con.size();
		}

		bool empty()
		{
			return _con.empty();
		}

		const T& top()
		{
			return _con.back();
		}
	private: container _con;
	};
}
