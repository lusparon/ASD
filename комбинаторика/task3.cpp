 /*
Задание 3. Комбинаторика
Написать алгоритм, выполняющий факторизацию числа. Построить график зависимости времени работы 
алгоритма от порядка числа (количества десятичных цифр в числе) для трех классов чисел: простые 
числа, случайные целые и целые, для которых делители не превосходят 7. Например, к третьему классу 
относится 6879707136=220*38.

*/

#include <iostream>
#include <vector>
#include <ctime> 

using namespace std;

void factorize(unsigned __int64 n) 
{
	for (unsigned __int64 i = 2; i <= n; i++) 
		while (n % i == 0 && n >= 1) 
		{
			cout << i << " ";
			n /= i;
		}
}

// n - количесвто цифр в рандомном числе
void random_factorize(__int64 n)
{
	unsigned __int64 nn = pow(10, n - 1);
	unsigned __int64 r = nn + rand() % (nn * 10 - 1);
	cout << "Random value: " << r << endl;
	for (unsigned __int64 i = 2; i <= r; i++)
		while (r % i == 0 && r >= 1)
		{
			cout << i << " ";
			r /= i;
		}
}

// целые, для которых делители не превосходят 7
void factorize_dividers_not_over_7(unsigned __int64 n)
{

	for (unsigned __int64 i = 2; i <= n; i++)
		while (n % i == 0 && n >= 1)
		{
			cout << i << " ";
			if (i > 7)
			{
				unsigned __int64 nn = n + 1;
				cout << endl;
				cout << "New n: " << nn << endl;
				factorize_dividers_not_over_7(nn);
			}
			n /= i;
		}
}

/*
int main()
{
	unsigned __int64 n;
	cout << "Input: ";
	cin >> n;

	// Для простых чисел
	time_t start = clock();
	factorize(n);
	cout.precision(20);
	cout << "; Time: " << double(clock() - start) / CLOCKS_PER_SEC << " seconds\n\n";

	// Для рандомных чисел
	unsigned __int64 n1;
	cout << "Input range random value: ";
	cin >> n1;
	time_t start2 = clock();
	srand(time(NULL));
	random_factorize(n1); // n1 - количесвто цифр в рандомном числе
	cout.precision(20);
	cout << "; Time: " << double(clock() - start2) / CLOCKS_PER_SEC << " seconds\n";

	// Для чисел, у которых делители не превосходят 7
	unsigned __int64 n2;
	cout << "Input number dividers_not_over_7: ";
	cin >> n2;
	time_t start3 = clock();
	srand(time(NULL));
	factorize_dividers_not_over_7(n2);
	cout.precision(20);
	cout << "; Time: " << double(clock() - start3) / CLOCKS_PER_SEC << " seconds\n";
	
	system("pause");
}*/
