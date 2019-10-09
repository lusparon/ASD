#include "Header.h"

void main()
{
	setlocale(LC_ALL,"RUSSIAN");
	//task 17
	cout << "------------------------------TASK 17------------------------------\n\n";
	vector<int> wtc{5,6,7,2,1,9};
	vector<int> costs{100,24,57,11,98,34};
	int W = 15;
	cout << "Массив весов :      ";
	for (auto x : wtc)
		cout << x << " ; ";
	cout << endl;
	cout << "Массив стоимостей : ";
	for (auto x : costs)
		cout << x << " ; ";
	cout << endl;
	cout << "Вместимость рюкзака : " << W << endl;
	cout << "Максимальная стоимость, которую можно набрать : " << knapsack(wtc, costs, W) << "\n\n";


	//task 2
	cout << "------------------------------TASK 2------------------------------\n\n";
	cout << "Пример 1 : " << endl;
	string s = "<]{}}([])<";
	cout << "Входная строка : " << s << endl;
	cout << "Результат : " << correct_bracket_seq(s) << "\n\n";

	cout << "Пример 2 : " << endl;
	string s1 = "<({[";
	cout << "Входная строка : " << s1 << endl;
	cout << "Результат : " << correct_bracket_seq(s1) << "\n\n";

	cout << "Пример 3 : " << endl;
	string s2 = ">)]{()]<<<{})))>";
	cout << "Входная строка : " << s2 << endl;
	cout << "Результат : " << correct_bracket_seq(s2) << "\n\n";

	cout << "Пример 4 : " << endl;
	string s3 = "<<<}}}][[])()(";
	cout << "Входная строка : " << s3 << endl;
	cout << "Результат : " << correct_bracket_seq(s3) << "\n\n";

	//task 12
	cout << "------------------------------TASK 12------------------------------\n\n";
	int a = 2;
	int sum = 1028;
	cout << "Все степени числа " << a << " сумма которых равна " << sum << " : ";
	for (auto x : efficient_expression_evaluation(a, sum))
		cout << x << " ; ";
	cout << "\n";
	a = 5;
	sum = 78780;
	cout << "Все степени числа " << a << " сумма которых равна " << sum << " : ";
	for (auto x : efficient_expression_evaluation(a, sum))
		cout << x << " ; ";
	cout << "\n";
	a = 2;
	sum = 16;
	cout << "Все степени числа " << a << " сумма которых равна " << sum << " : ";
	for (auto x : efficient_expression_evaluation(a, sum))
		cout << x << " ; ";
	cout << "\n";

	a = 7;
	sum = 282511320;
	cout << "Все степени числа " << a << " сумма которых равна " << sum << " : ";
	for (auto x : efficient_expression_evaluation(a, sum))
		cout << x << " ; ";
	cout << "\n";

	system("pause");
}