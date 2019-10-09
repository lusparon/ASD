/*
--------------------------------
Input: 5
Count: 3
Time: 1.5900000000000000799 seconds
--------------------------------
Input: 7
Count: 8
Time: 1.7459999999999999964 seconds
*/

#include <iostream>
#include <time.h>
#include <algorithm>
#include <vector>

using namespace std;

// ����� ��������� ������� N
int count_bin_elems(int n)
{
	/*
	� ������� ���� ��������� �� ����� ���������� ���������� ������ �����, �������� ������������� ������� �������� N �������� ����, 
	��� ������� ����������� �������: � �������� ������ ����� �� ����������� ������ ��� ����.
	*/
	if (n < 4)
		return 1;
	else
		return count_bin_elems(n - 2) + count_bin_elems(n - 1);
}


/*int main() 
{
	setlocale(LC_ALL, "ru");

	time_t start1 = clock();
	int n;
	cout << "Input: ";
	cin >> n;
	cout << "Count: " << count_bin_elems(n) << endl;
	cout.precision(20);
	cout << "Time: " << double(clock() - start1) / CLOCKS_PER_SEC << " seconds\n" << endl;

	system("pause");
}*/