#include "List.h"

//Создание списка 
Mylist<int> create_intmylist(initializer_list<int> lst)
{
	Mylist<int> res;
	for (auto x : lst)
		res.push_back(x);
	return res;
};

//Задание 1
int countPositive(Mylist<int>& l)
{
	int count = 0;
	for_each(l.begin(), l.end(), [&count](int n) {if (n > 0) count++; });
	return count;
}

//Задание 2
void maxElCount(int& maxEl, int& count, Mylist<int>& l)
{
	count = 1;
	maxEl = *(l.begin());

	for_each(l.begin(), l.end(), [&count, &maxEl](int n)
	{
		if (n == maxEl) count++;
		if (n > maxEl)
		{
			maxEl = n;
			count = 1;
		}
	});
}

//Задание 3
void splitLists(Mylist<int>& in, Mylist<int>& neg, Mylist<int>& pos)
{
	neg = Mylist<int>();
	pos = Mylist<int>();
	for_each(in.begin(), in.end(), [&neg, &pos](int n)
	{
		if (n < 0) neg.push_back(n);
		else pos.push_back(n);
	});
}