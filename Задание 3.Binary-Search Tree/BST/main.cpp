#include <cassert>
#include <vector>
#include <ctime>
#include <set>
#include "BST.h"
#include "mySet.h"
using namespace std;

void main()
{
	setlocale(0, "");
 
	BST<int> tree(10);
	tree.insert(9);
	tree.insert(4);
	tree.insert(1);
	tree.insert(101);
	tree.insert(13);
	tree.insert(2);
	tree.insert(6);
 
	 cout << "Output: ";
	 tree.print();
	 cout << endl;
 
	 cout << "Output by \"layers\": ";
	 tree.print_layer();
	 cout << endl;
 
	 auto b = tree.begin();
	 cout << "begin: " << *b << endl;
 
	 auto e = tree.end();
	 cout << "end: " << *e << endl;
 
	 cout << "Output using iterators: ";
	 for (auto a = tree.begin(); a != tree.end(); ++a)
	 cout << *a << " ";
	 cout << endl;
 
	 auto mn = tree.min();
	 cout << "Minimum: " << *mn << endl;
 
	 auto mx = tree.max();
	 cout << "Maxsimum: " << *mx << endl;
 
	 cout << "find(6): " << *find(tree.begin(), tree.end(), 6) << endl;
 
	 cout << "Delete 6." << endl;
	 tree.remove(6);
 
	 cout << "find(6): " << *find(tree.begin(), tree.end(), 6) << endl;
 
	 cout << "count_if: " << count_if(tree.begin(), tree.end(), ([](int x) {return x % 2 == 0; })) << endl << endl;

	 cout << "---------Task 4---------\n\n";
	 cout.precision(16);
	 set<int> s;
	 mySet<int> mys;
	 int n = 100000;

	 cout << "n = " << n << endl;
	 // Вставка
	 unsigned int start_time = clock();
	 for (size_t i = 0; i < n; ++i)
		 s.insert(rand() % n);
	 cout << "set insert: " << (double)(clock() - start_time) / CLOCKS_PER_SEC << " seconds\n";

	 start_time = clock();
	 for (size_t i = 0; i < n; ++i)
		 mys.insert(rand() % n);
	 cout << "mySet insert: " << (double)(clock() - start_time) / CLOCKS_PER_SEC << " seconds\n\n";

	 // Поиск
	 start_time = clock();
	 for (size_t i = 1; i < n; i++)
		 s.find(rand() % n);
	 cout << "set find: " << (double)(clock() - start_time) / CLOCKS_PER_SEC << " seconds\n";

	 start_time = clock();
	 for (size_t i = 1; i < n; i++)
		 mys.find(rand() % n);
	 cout << "mySet find: " << (double)(clock() - start_time) / CLOCKS_PER_SEC << " seconds\n\n";

	 // Удаление
	 start_time = clock();
	 for (size_t i = 1; i < n; i++)
		 s.erase(rand() % n);
	 cout << "set erase: " << (double)(clock() - start_time) / CLOCKS_PER_SEC << " seconds\n";

	 start_time = clock();
	 for (size_t i = 1; i < n; i++)
		 mys.erase(rand() % n);
	 cout << "mySet erase: " << (double)(clock() - start_time) / CLOCKS_PER_SEC << " seconds\n\n";

	 // Решето Эратосфена
	 int n1 = 10000;
	 auto start = clock();
	 int *a = new int[n1 + 1];
	 for (int i = 0; i < n1 + 1; i++)
		 a[i] = i;
	 for (int p = 2; p < n1 + 1; p++)
	 {
		 if (a[p] != 0)
		 {
			 for (int j = p * p; j < n1 + 1; j += p)
				 a[j] = 0;
		 }
	 }
	 cout << "Array Eratosthenes: " << double(clock() - start) / CLOCKS_PER_SEC << " seconds\n";

	 mySet<int> mys2;
	 start = clock();
	 for (int i = 0; i < n1; i++)
		 mys2.insert(i);
	 for (int i = 2; i * i <= n1; i++)
	 {
		 if (!mys2.find(i))
			 continue;
		 int x = i * i;
		 while (x <= n1)
		 {
			 mys2.erase(x);
			 x += i;
		 }
	 }
	 cout << "mySet Eratosthenes: " << double(clock() - start) / CLOCKS_PER_SEC << " seconds\n";
 
	 system("pause");
}

