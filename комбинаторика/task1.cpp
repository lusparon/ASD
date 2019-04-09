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
	// ���������� ������������ � ��������� �������� ������
	static size_t assigns, compares;
	// ����������� - ������������� ��������� ���������
	elem() {
		data = rand();
	};
	// ���������� �����������
	elem(const elem & other) : data(other.data) {
		++assigns;
	};
	// ����� ���������
	static void reset() {
		assigns = 0;
		compares = 0;
	}
	// ���������� �������� ��������� - ��� ���������� ����������
	bool operator<(const elem &other) const {
		++compares;
		return data<other.data;
	}
	// ���������� ��������� ������������
	const elem &operator=(const elem &other) {
		++assigns;
		data = other.data;
		return *this;
	}
	// ������������� ������� - �������� "��������� � �����"
	friend std::ostream & operator<<(std::ostream & out, const elem & item);
};

// ������������� ����������� ����� ������
size_t elem::assigns = 0;
size_t elem::compares = 0;

// ���������� �������� ������ � ����� - ��� ������������� �������
std::ostream & operator<<(std::ostream & out, const elem & item) {
	return out << item.data;
}

// ���������� ��������� ��� �������
void insertionsort(std::vector<elem> & vect)
{
	for (size_t i = 1, j = i; i < vect.size(); j = ++i)
		while (j > 0 && vect[j] < vect[j - 1])
		{
			std::swap(vect[j], vect[j - 1]);
			--j;
		}
};

// ����������� ���������� ��� �������
void bubblesort(std::vector<elem> & vect) {
	for (size_t i = vect.size() - 1; i>0; --i)
		for (size_t j = 0; j<i; ++j)
			if (vect[j + 1]<vect[j])
				std::swap(vect[j + 1], vect[j]);
}

// ������� ���������� ��� ������� - �������� ����������� ����������
void quicksort(std::vector<elem> & vect) {
	sort(vect.begin(), vect.end());
}

// ���������� ���������� ��� ������� - �������� ����������� ����������
void stablesort(std::vector<elem> & vect) {
	stable_sort(vect.begin(), vect.end());
}

/*int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");

	cout << "-----------------������� 1.-----------------" << endl;
	// �������������� ��������� ��������� �����
	srand(static_cast<unsigned int>(time(NULL)));
	// ��������� ��� ���������� ������� ���������� �������
	cout << "Vector size : ";
	size_t n;
	cin >> n;
	vector<elem> v1(n), v2(v1), v3(v2), v4(v3);

	// ������� ���������� � ����������� ������������ � ���������
	cout << "Vectors created : " << v1.size() << " elements\n";
	cout << "Assigns : " << elem::assigns << " comparisons : ";
	cout << elem::compares << endl << endl;
	// ��������� ��������� ��������� � ���������� ����������
	elem::reset();

	//-------------Quick sort-------------
	time_t start1 = clock();
	// ������� ���������� - �������� �� ����������� ���������� C++
	quicksort(v1);
	cout.precision(20);
	// ������� ���������� � ����������� ������������ � ��������� � �������� ����������
	cout << "Quick sort: assigns : " << elem::assigns;
	cout << " comparisons : " << elem::compares << endl;
	cout << "Time quicksort: " << double(clock() - start1) / CLOCKS_PER_SEC << " seconds\n" << endl;
	elem::reset();

	//-------------Stable sort-------------
	time_t start2 = clock();
	// ���������� ���������� ��� ������� - �������� ����������� ����������
	stablesort(v2);
	cout.precision(20);
	cout << "Stable sort: assigns : " << elem::assigns;
	cout << " comparisons : " << elem::compares << endl;
	cout << "Time stablesort: " << double(clock() - start2) / CLOCKS_PER_SEC << " seconds\n" << endl;
	elem::reset();

	//-------------Insertion sort-------------
	time_t start3 = clock();
	// ���������� ��������� ��� �������
	insertionsort(v3);
	// ������� ���������� � ����������� ������������ � ��������� � �������� ����������
	cout << "Insertion sort: assigns : " << elem::assigns;
	cout << " comparisons : " << elem::compares << endl;
	cout << "Time insertionsort: " << double(clock() - start3) / CLOCKS_PER_SEC << " seconds\n" << endl;
	elem::reset();

	//-------------Bubble sort-------------
	time_t start4 = clock();
	// ����������� ����������
	bubblesort(v4);
	cout.precision(20);
	cout << "Bubble sort: assigns : " << elem::assigns;
	cout << " comparisons : " << elem::compares << endl;
	cout << "Time bubblesort: " << double(clock() - start4) / CLOCKS_PER_SEC << " seconds\n" << endl;
	elem::reset();

	system("PAUSE");

}*/
