#include <time.h>
#include <iostream>
#include <list>

#include "PQueue.h"
#include "HPQueue.h"
#include <intrin.h>
#include <iostream>
#include <fstream>
#include <queue>


struct measured_string
{
private:
	std::string data;
public:
	measured_string(std::string s) : data(s)
	{}

	int length()
	{
		return data.length();
	}

	friend bool operator > (measured_string ms1, measured_string ms2)
	{
		return ms1.length() > ms2.length();
	}

	friend bool operator < (measured_string ms1, measured_string ms2)
	{
		return ms1.length() < ms2.length();
	}


	friend std::ostream& operator<<(std::ostream& os, const measured_string& ms)
	{
		os << ms.data;
		return os;
	}

};

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	cout << "Задание 1 : " << endl;
	PQueue<int> pq = PQueue<int>({ 3,52,1,-2,6,0,4 });
	std::cout << "Очередь: " << pq << "\n";
	pq.add(-5);
	std::cout << "Добавление в очередь -5 : " << pq << "\n";
    pq.add(1);
	std::cout << "Добавление в очередь 1: " << pq << "\n";
	pq.add(7);
	std::cout << "Добавление в очередь 7: " << pq << "\n";
	pq.add(55);
	std::cout << "Добавление в очередь 55: " << pq << "\n";

	cout << "Задание 2 : " << endl;
	std::cout << "Максимальный элемент: " << pq.maxElem() << "\n";

	cout << "Задание 3 : " << endl;
	std::vector<int> arr = { 5,-32,4,254,2,5,21,1,-45,68,1,0,37 };
	PQueue<int> pq1 = PQueue<int>(arr);
	std::cout << "Создание очереди из массива элементов: " << pq1 << "\n";

	cout << "Задание 4 : " << endl;
	pq.merge(pq1);
	std::cout << "Слияние двух очередей с приоритетами: " << pq << "\n";

	cout << "ЧАСТЬ 2 : " << endl;

	HPQueue<int> hpq = HPQueue<int>({ 5,3,16,1,9,2,6,12,3, 6, 31, -2, 45, 445 });
	
	HPQueue<std::string> hpq1 = HPQueue<std::string>({ "adw", "za", "edmddm", "awddfs", "zezeze" });

	cout << "Cравнение эффективности : " << endl;

	auto test_pq = std::priority_queue<int>();
	auto test_hpq = HPQueue<int>();

	std::cout << "RAND_MAX = " << RAND_MAX << std::endl;

	clock_t start, stop;
	

	auto nums = std::vector<int>();
	for (int i = 0; i < 400000; i++)
	{
		int rn = rand();
		nums.push_back(rn);
	}

	int time_in_pq, time_in_hpq, time_out_pq, time_out_hpq;

	start = __rdtsc();

	for (int i = 0; i < 400000; i++)
	{
		test_pq.push(nums[i]);
	}

	stop = __rdtsc();

	time_in_pq = stop - start;

	start = __rdtsc();

	for (int i = 0; i < 400000; i++)
	{
		test_hpq.add(nums[i]);
	}

	stop = __rdtsc();

	time_in_hpq = stop - start;

	for (int i = 0; i < 400000; i++)
	{
		test_pq.pop();
	}

	stop = __rdtsc();

	time_out_pq = stop - start;

	start = __rdtsc();

	for (int i = 0; i < 400000; i++)
	{
		test_hpq.extractMax();
	}

	stop = __rdtsc();

	time_out_hpq = stop - start;

	std::cout << "Стандартный PQ: ввод " << time_in_pq << ", вывод " << time_out_pq << "\n";
	std::cout << "Мой PQ: ввод " << time_in_hpq << ", вывод " << time_out_hpq << "\n";

	cout << "Война и мир : " << endl;

	std::cout << "PQ для строк, лексикогрфическое сравнение: " << hpq1 << "\n";

	auto hpq2 = HPQueue<measured_string, std::less<measured_string>>({ measured_string("adw"), measured_string("adddw"),  measured_string("aw"), });

	std::cout << "PQ для строк, сравнение по длине: " << hpq2 << "\n";
	
	std::ifstream myfile("войнаимир.txt");

	auto hpq3 = HPQueue<measured_string, std::less<measured_string>>();

	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			std::string s;
			myfile >> s;
			//while (ispunct(s.back())) s.erase(s.begin() + (s.size() - 1), s.end());;
			hpq3.add(measured_string(s));
		}
		myfile.close();
	}

	std::cout << "Двадцать самых длинных слов из \"войны и мира\": \n";
	for (int i = 1; i < 101; i++)
	{
		std::cout << "#" << i << ": " << hpq3.extractMax() << " \n";
	}
	system("PAUSE");
	return 0;

}
