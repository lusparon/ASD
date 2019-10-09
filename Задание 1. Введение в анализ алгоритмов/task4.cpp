/*
Задание 4. Переборный алгоритм
Сколько существует четных чисел, принадлежащих диапазону [10^10;10^11), для которых выполняется 
правило: в записи числа не встречается подряд две цифры, являющихся простыми числами (2, 3, 5, 7)?

*/

#include <iostream>
#include <ctime>

using namespace std;

// Проверка правила: в записи числа не встречается подряд две цифры, являющихся простыми числами (2, 3, 5, 7)
bool two_digits_is_prime_nembers(unsigned __int64 n)
{
	int count = 0;
	do
	{
		if (n % 10 == 2 || n % 10 == 3 || n % 10 == 5 || n % 10 == 7)
		{
			count += 1;
			if (count == 2)
				return true;
		}
		else
			count = 0;
		n /= 10;
	} while (n > 0);
	return false;
}

unsigned __int64 count_with_two_prime_numbers()
{
	unsigned __int64 count = 0;
	for (unsigned __int64 i = pow(10,10); i < pow(10, 11); i++)
		if (!two_digits_is_prime_nembers(i) && i % 2 == 0)
			++count;
	return count;
}

int main()
{
	time_t start = clock();
	cout << "Count even and two in a row prime numbers in range [10^10;10^11) = " << count_with_two_prime_numbers() << endl;
	cout.precision(20);
	cout << "; Time: " << double(clock() - start) / CLOCKS_PER_SEC << " seconds\n";

	system("pause");
}