#ifndef HEAP_H
#define HEAP_H

#include <algorithm>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

template<typename T, typename Container = std::vector<T>, typename Cmp = std::less<T>>
class Heap
{
protected:
	Container data;
	Cmp cmp;

	void heapify(int i)
	{
		int leftChild, rightChild, greatestChild;
		while (true)
		{
			leftChild = 2 * i + 1;
			rightChild = 2 * i + 2;
			greatestChild = i;

			if (leftChild < data.size() && cmp(data[greatestChild], data[leftChild]))
				greatestChild = leftChild;
			if (rightChild < data.size() && cmp(data[greatestChild], data[rightChild]))
				greatestChild = rightChild;

			if (greatestChild == i) break;
			std::swap(data[i], data[greatestChild]);
			i = greatestChild;
		}
	}


	void buildHeap(Container c)
	{
		data = c;
		for (int i = data.size() / 2 - 1; i >= 0; i--)
		{
			heapify(i);
		}
	}

public:

	Heap() : data()
	{}

	Heap(std::initializer_list<T> il) : data()
	{
		for (auto x : il)
			add(x);
	}

	Heap(const Heap<T>& h) : data(h.data)
	{}

	int size()
	{
		return data.size();
	}
	
	void add(T value)
	{
		data.push_back(value);
		int i = size() - 1;
		int parent = (i - 1) / 2;
		while (i > 0 && cmp(data[parent], data[i]))
		{
			std::swap(data[i], data[parent]);
			i = parent;
			parent = (i - 1) / 2;
		}
	}

	T extractMax()
	{
		T res = data[0];
		std::swap(data[0], data[size()-1]);
		data.pop_back();
		heapify(0);
		return res;
	}

	bool empty()
	{
		return size() == 0;
	}

};

#endif // !HEAP_H
