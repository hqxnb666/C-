#pragma once
#include <deque>
#include <list>
#include <vector>
#include <algorithm> // 确保包含了swap的定义

namespace bit
{
    template <class T, class Container = std::deque<T>>
    class queue
    {
    public:
        void push(const T& x)
        {
            _con.push_back(x);
        }

        void pop()
        {
            _con.pop_front();
        }

        size_t size() const
        {
            return _con.size();
        }

        bool empty() const
        {
            return _con.empty();
        }

        const T& front() const
        {
            return _con.front();
        }

        const T& back() const
        {
            return _con.back();
        }
    private:
        Container _con;
    };

    template <class T>
    class less
    {
    public:
        bool operator()(const T& x, const T& y) const
        {
            return x < y;
        }
    };

    template<class T, class Container = std::vector<T>, class Compare = less<T>>
    class priority_queue
    {
    public:
        void adjust_up(size_t child)
        {
            Compare com;
            int parent = (child - 1) / 2;
            while (child > 0)
            {
                if (com(_con[parent], _con[child]))
                {
                    std::swap(_con[child], _con[parent]);
                    child = parent;
                    parent = (child - 1) / 2;
                }
                else
                {
                    break;
                }
            }
        }

        void push(const T& x)
        {
            _con.push_back(x);
            adjust_up(_con.size() - 1);
        }

        void adjust_down(size_t parent)
        {
            Compare com;
            size_t child = parent * 2 + 1;
            while (child < _con.size())
            {
                if (child + 1 < _con.size() && com(_con[child], _con[child + 1]))
                {
                    child += 1;
                }
                if (com(_con[parent], _con[child]))
                {
                    std::swap(_con[child], _con[parent]);
                    parent = child;
                    child = child * 2 + 1;
                }
                else
                {
                    break;
                }
            }
        }

        void pop()
        {
            std::swap(_con[0], _con[_con.size() - 1]);
            _con.pop_back();
            adjust_down(0);
        }

        bool empty() const
        {
            return _con.empty();
        }

        size_t size() const
        {
            return _con.size();
        }

        const T& top() const
        {
            return _con[0];
        }
    private:
        Container _con;
    };
}
