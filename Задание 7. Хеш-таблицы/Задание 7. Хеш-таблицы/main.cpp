#include "HashTable.h"
#include <unordered_set>
#include <random>
#include <ctime>
#include "RBT.h"

using namespace std;

void main()
{
	default_random_engine engine(time(0));
	uniform_int_distribution<> dist(0);
	size_t size = 200000;
	size_t half_size = 20000;
	vector<size_t> randoms(size);
	for (size_t i = 0; i < randoms.size(); ++i)
	{
		randoms[i] = dist(engine);
	}
	cout.precision(20);
	unordered_set<size_t> uset;
	RBT<size_t> rbt;
	HashTable ht; 
	for (size_t i = 0; i < half_size; ++i)
	{
		size_t x = dist(engine);
		size_t y = dist(engine);
		ht.Insert(x , y);
		uset.insert(x);
		rbt.insert(x);
	}

    //ht.print();

	size_t n = 20000;
	time_t start = clock();
	for (size_t i = 0; i <= n; i += 100)
	{
		for (size_t j = 0; j < 100; ++j)
		{
			uset.insert(randoms[i + j]);
		}
		for (size_t j = 0; j < 500; ++j)
		{
			uset.find(randoms[dist(engine) % randoms.size()]);
		}
		for (size_t j = 0; j < 100; ++j)
		{
			uset.erase(randoms[i + j]);
		}
	}
	cout << "unordered_set: " << double(clock() - start) / CLOCKS_PER_SEC << "s\n";

	time_t start2 = clock();
	for (size_t i = 0; i <= n; i += 100)
	{
		for (size_t j = 0; j < 100; ++j)
		{
			ht.Insert(randoms[i + j]);
		}
		for (size_t j = 0; j < 500; ++j)
		{
			ht.SearchKey(randoms[dist(engine) % randoms.size()]);
		}
		for (size_t j = 0; j < 100; ++j)
		{
			ht.Remove(randoms[i + j]);
		}
	}
	cout << "my HashTable : " << double(clock() - start2) / CLOCKS_PER_SEC << "s\n";

	/*time_t start3 = clock();
	for (size_t i = 0; i <= n; i += 100)
	{
		for (size_t j = 0; j < 100; j++)
		{
			rbt.insert(randoms[i + j]);
		}
		for (size_t j = 0; j < 50; j++)
		{
			rbt.find(randoms[dist(engine) % randoms.size()]);
		}
		for (size_t j = 0; j < 100; j++)
		{
			rbt.remove(randoms[i + j]);
		}
	}
	cout << "my RBT : " << double(clock() - start3) / CLOCKS_PER_SEC << "s\n";*/
	

	system("pause");
}