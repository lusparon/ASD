#ifndef PQueue_h
#define PQueue_h
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <string>

using namespace std;

template<typename T, typename Container = std::vector<T> , typename Cmp = std::less<T>>
class PQueue
{
	Container data;
	Cmp cmp;
public:
	PQueue() : data() {}

	PQueue(std::initializer_list<T> il) : data()
	{
		for (auto x : il)
			add(x);
	}

	PQueue(Container v) : data()
	{
		for (auto x : v)
			add(x);
	}

	//Добавление элемента
	void add(T x)
	{
		if (data.empty()) data.push_back(x);
		else
		{
			int i = 0;

			while (cmp(data[i], x))
			{
				if (i == data.size() - 1)
				{
					data.push_back(x);
					return;
				}
				else i++;
			}
			data.insert(data.cbegin() + i, x);
		}
	}

	//Максимальный
	T maxElem()
	{
		return data.front();
	}

	//Слияние
	void merge(PQueue<T> &p)
	{
		for (auto x : p.data)
			add(x);
	}

	//Операции вывода в поток
	friend std::ostream& operator << (std::ostream& os, PQueue<T> &p)
	{
		for (auto x : p.data)
			os << x << " ";
		return os;
	}
};



#endif PQueue_h

