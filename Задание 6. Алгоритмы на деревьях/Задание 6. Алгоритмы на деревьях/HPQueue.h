#ifndef  HPQUEUE_H
#define HPQUEUE_H

#include "Heap.h"
#include <string>

template<typename T, typename comp = std::less<T>>
class HPQueue : public Heap<T, std::vector<T>, comp>
{
public:
	HPQueue() : Heap<T, std::vector<T>, comp>()
	{}

	HPQueue(const HPQueue<T>& q1) : Heap<T, std::vector<T>, comp>()
	{
		this->buildHeap(q1.data);
	}

	HPQueue(std::initializer_list<T> il) : Heap<T, std::vector<T>, comp>()
	{
		this->buildHeap(il);
	}

	void merge(HPQueue<T> pq)
	{
		for (auto x : pq.data)
			add(x);
	}

	friend std::ostream& operator<<(std::ostream& os, const HPQueue<T, comp>& p)
	{
		HPQueue pq1(p);
		while (!pq1.empty())
			os << pq1.extractMax() << " ";
		return os;
	}

};
#endif // ! HPQUEUE_H