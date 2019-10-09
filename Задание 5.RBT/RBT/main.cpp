#include <iostream>
#include <ctime>
#include <set>
#include "RBT.h"

using namespace std;

void main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    
    RBT<int> tree;
    int n = 100;
	for (size_t i = 0; i < n; i+=2)
		tree.insert(i);//(rand() % n);
	for (auto it = tree.begin(); it != tree.end(); ++it)
		cout << *it << " ";
	cout << endl;
	tree.print_infix();
	cout << endl;
	//tree.input_file("RBTree.txt");
    //tree.output_file("RBTree(1).txt");

    
	RBT<int> testTree1, testTree2;
	testTree1.insert(10);
	testTree1.insert(20);
	testTree1.insert(30);

	testTree2.insert(10);
	testTree2.insert(5);
	testTree2.insert(15);
	testTree2.insert(25);
	testTree2.insert(30);
	testTree2.insert(35);


	testTree1.print_infix();
	cout << endl;

	testTree2.print_infix();
	cout << endl;

	cout << "lower_bound(-100): " << *testTree2.lower_bound(-100) << endl;
	cout << "lower_bound(12): " << *testTree2.lower_bound(12) << endl;
	cout << "lower_bound(21): " << *testTree2.lower_bound(21) << endl;
	cout << "lower_bound(35): " << *testTree2.lower_bound(35) << endl;
	cout << "lower_bound(36): " << *testTree2.lower_bound(36) << endl;
	cout << endl;

	cout << "upper_bound(-100): " << *testTree2.upper_bound(-100) << endl;
	cout << "upper_bound(12): " << *testTree2.upper_bound(12) << endl;
	cout << "upper_bound(21): " << *testTree2.upper_bound(21) << endl;
	cout << "upper_bound(35): " << *testTree2.upper_bound(35) << endl;
	cout << "upper_bound(36): " << *testTree2.upper_bound(36) << endl;

    cout << "find(12): " << *tree.find(12) << endl;
    
    tree.remove(12);
    cout << "remove 12." << endl;
    
	cout << "find(12): " << *tree.find(12) << endl;

    tree.print_infix();
	cout << "amount of rotations: " << tree.rotations() << endl;
    cout << endl;

	cout << "find(12): " << *tree.find(12) << endl;

	tree.insert(12);
	cout << "insert 12" << endl;

	tree.print_infix();
	cout << "amount of rotations: " << tree.rotations() << endl;
	cout << endl;
	
	cout << "find(12): " << *tree.find(12) << endl;

    
    cout << "lower_bound(-1000): " << *tree.lower_bound(-1000) << endl;
    cout << "lower_bound(1000): " << *tree.lower_bound(1000) << endl;
	cout << "lower_bound(56): " << *tree.lower_bound(56) << endl;
	cout << "lower_bound(55): " << *tree.lower_bound(55) << endl;
    
    cout << "upper_bound(-1000): " << *tree.upper_bound(-1000) << endl;
    cout << "upper_bound(1000): " << *tree.upper_bound(1000) << endl;
	cout << "upper_bound(53): " << *tree.upper_bound(53) << endl;
	cout << "upper_bound(52): " << *tree.upper_bound(52) << endl;
    
    
    cout << endl << "                          set comparing" << endl << endl;
    
    
    RBT<int> myt;
    set<int> s;
    
    int len = 10000;
    // Вставка
    unsigned int start_time = clock();
    for (size_t i = 0; i < len; ++i)
        myt.insert(rand() % len);
    cout << "RBTree insert: " << (double)(clock() - start_time) / CLOCKS_PER_SEC << " seconds\n";
    
    start_time = clock();
    for (size_t i = 0; i < len; ++i)
        s.insert(rand() % len);
    cout << "set insert: " << (double)(clock() - start_time) / CLOCKS_PER_SEC << " seconds\n\n";
    
    // Поиск
    start_time = clock();
    for (size_t i = 1; i < len; i++)
        myt.find(rand() % len);
    cout << "RBTree find: " << (double)(clock() - start_time) / CLOCKS_PER_SEC << " seconds\n";
    
    start_time = clock();
    for (size_t i = 1; i < len; i++)
        s.find(rand() % len);
    cout << "set find: " << (double)(clock() - start_time) / CLOCKS_PER_SEC << " seconds\n\n";
    
    system("pause");
}

