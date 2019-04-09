/*
---------------------------------(ctrl+F5)
Vector size : 5000
Vectors created : 5000 elements
Assigns : 15000 comparisons : 0

Quick sort: assigns : 94409 comparisons : 141246
Time quicksort: 0.02999999999999999889 seconds

Stable sort: assigns : 96281 comparisons : 131468
Time stablesort: 0.026999999999999999695 seconds

Insertion sort: assigns : 18794862 comparisons : 6269948
Time insertionsort: 12.535000000000000142 seconds

Bubble sort: assigns : 18794862 comparisons : 12497500
Time bubblesort: 17.765999999999998238 seconds
*/
#include <time.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

class elem {
	int data;
public:
	// Количество присваиваний и сравнений объектов класса
	static size_t assigns, compares;
	// Конструктор - инициализация случайным значением
	elem() {
		data = rand();
	};
	// Копирующий конструктор
	elem(const elem & other) : data(other.data) {
		++assigns;
	};
	// Сброс счетчиков
	static void reset() {
		assigns = 0;
		compares = 0;
	}
	// Перегрузка операции сравнения - для сортировок достаточно
	bool operator<(const elem &other) const {
		++compares;
		return data<other.data;
	}
	// Перегрузка оператора присваивания
	const elem &operator=(const elem &other) {
		++assigns;
		data = other.data;
		return *this;
	}
	// Дружественная функция - операция "поместить в поток"
	friend std::ostream & operator<<(std::ostream & out, const elem & item);
};

// Инициализация статических полей класса
size_t elem::assigns = 0;
size_t elem::compares = 0;

// Перегрузка операции вывода в поток - как дружественная функция
std::ostream & operator<<(std::ostream & out, const elem & item) {
	return out << item.data;
}

// Сортировка вставками для вектора
void insertionsort(std::vector<elem> & vect)
{
	for (size_t i = 1, j = i; i < vect.size(); j = ++i)
		while (j > 0 && vect[j] < vect[j - 1])
		{
			std::swap(vect[j], vect[j - 1]);
			--j;
		}
};

// Пузырьковая сортировка для вектора
void bubblesort(std::vector<elem> & vect) {
	for (size_t i = vect.size() - 1; i>0; --i)
		for (size_t j = 0; j<i; ++j)
			if (vect[j + 1]<vect[j])
				std::swap(vect[j + 1], vect[j]);
}

// Быстрая сортировка для вектора - алгоритм стандартной библиотеки
void quicksort(std::vector<elem> & vect) {
	sort(vect.begin(), vect.end());
}

// Устойчивая сортировка для вектора - алгоритм стандартной библиотеки
void stablesort(std::vector<elem> & vect) {
	stable_sort(vect.begin(), vect.end());
}

/*int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");

	cout << "-----------------Задание 1.-----------------" << endl;
	// Инициализируем генератор случайных чисел
	srand(static_cast<unsigned int>(time(NULL)));
	// Объявляем два идентичных вектора указанного размера
	cout << "Vector size : ";
	size_t n;
	cin >> n;
	vector<elem> v1(n), v2(v1), v3(v2), v4(v3);

	// Выводим информацию о количествах присваиваний и сравнений
	cout << "Vectors created : " << v1.size() << " elements\n";
	cout << "Assigns : " << elem::assigns << " comparisons : ";
	cout << elem::compares << endl << endl;
	// Выполняем обнуление счетчиков и устойчивую сортировку
	elem::reset();

	//-------------Quick sort-------------
	time_t start1 = clock();
	// Быстрая сортировка - алгоритм из стандартной библиотеки C++
	quicksort(v1);
	cout.precision(20);
	// Выводим информацию о количествах присваиваний и сравнений в процессе сортировки
	cout << "Quick sort: assigns : " << elem::assigns;
	cout << " comparisons : " << elem::compares << endl;
	cout << "Time quicksort: " << double(clock() - start1) / CLOCKS_PER_SEC << " seconds\n" << endl;
	elem::reset();

	//-------------Stable sort-------------
	time_t start2 = clock();
	// Устойчивая сортировка для вектора - алгоритм стандартной библиотеки
	stablesort(v2);
	cout.precision(20);
	cout << "Stable sort: assigns : " << elem::assigns;
	cout << " comparisons : " << elem::compares << endl;
	cout << "Time stablesort: " << double(clock() - start2) / CLOCKS_PER_SEC << " seconds\n" << endl;
	elem::reset();

	//-------------Insertion sort-------------
	time_t start3 = clock();
	// Сортировка вставками для вектора
	insertionsort(v3);
	// Выводим информацию о количествах присваиваний и сравнений в процессе сортировки
	cout << "Insertion sort: assigns : " << elem::assigns;
	cout << " comparisons : " << elem::compares << endl;
	cout << "Time insertionsort: " << double(clock() - start3) / CLOCKS_PER_SEC << " seconds\n" << endl;
	elem::reset();

	//-------------Bubble sort-------------
	time_t start4 = clock();
	// Пузырьковая сортировка
	bubblesort(v4);
	cout.precision(20);
	cout << "Bubble sort: assigns : " << elem::assigns;
	cout << " comparisons : " << elem::compares << endl;
	cout << "Time bubblesort: " << double(clock() - start4) / CLOCKS_PER_SEC << " seconds\n" << endl;
	elem::reset();

	system("PAUSE");

}*/
