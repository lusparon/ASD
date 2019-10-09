#include "List.h"
#include "Elem.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	clock_t start, stop;
	int cp, count, max;
	Mylist<int> list1, list2;
	list1.push_back(10);

	//Проверка работы итераторов
	assert(++--list1.end() == list1.end());
	assert(list2.end() != list1.end());
	assert(list1.end() == list1.end());
	cout << "Iterator tests : successful" << endl;
	cout << endl;

	list2.push_back(17);
	list2.push_back(12);
	list2.push_back(23);
	list2.push_back(34);
	list2.push_back(-98);
	list2.push_back(-20);
	list2.push_back(8);

	//Задание 1
	unsigned int start_time = clock();
	cp = countPositive(list2);
	unsigned int end_time = clock();
	cout << "Task 1 : " <<(end_time - start_time) << " milliseconds\n";
	assert(cp == 5);
	
	//Задание 2
	Mylist<int> list3 = create_intmylist({8, 12, 5, -9, 17, -78, 24, 3 , 6, 2, 24, 9, 11});
	start_time = clock();
	maxElCount(max, count, list3);
	cout << "Task 2 : " << (double)(clock() - start_time) << " milliseconds\n";
	assert(max == 24 && count == 2);

	//Задание 3
	Mylist<int> list4, list5;
	start_time = clock();
	splitLists(list3, list4, list5);
	cout << "Task 3 : " << (double)(clock() - start_time) << " milliseconds\n";
	cout << "Start list : " << list3 << endl;
	cout << "Negative elements: " << list4 << endl;
	cout << "Positive elements: " << list5 << endl;

	//Задание 4
	start_time = clock();
	list5.reverse();
	cout << "Task 4 : " << (double)(clock() - start_time) << " milliseconds\n";
	cout << "Reverse last list: " << list5 << endl;

	system("PAUSE");
	return 0;

}
