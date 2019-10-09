#include "Header.h"

void main()
{
	setlocale(LC_ALL,"RUSSIAN");
	//task 17
	cout << "------------------------------TASK 17------------------------------\n\n";
	vector<int> wtc{5,6,7,2,1,9};
	vector<int> costs{100,24,57,11,98,34};
	int W = 15;
	cout << "������ ����� :      ";
	for (auto x : wtc)
		cout << x << " ; ";
	cout << endl;
	cout << "������ ���������� : ";
	for (auto x : costs)
		cout << x << " ; ";
	cout << endl;
	cout << "����������� ������� : " << W << endl;
	cout << "������������ ���������, ������� ����� ������� : " << knapsack(wtc, costs, W) << "\n\n";


	//task 2
	cout << "------------------------------TASK 2------------------------------\n\n";
	cout << "������ 1 : " << endl;
	string s = "<]{}}([])<";
	cout << "������� ������ : " << s << endl;
	cout << "��������� : " << correct_bracket_seq(s) << "\n\n";

	cout << "������ 2 : " << endl;
	string s1 = "<({[";
	cout << "������� ������ : " << s1 << endl;
	cout << "��������� : " << correct_bracket_seq(s1) << "\n\n";

	cout << "������ 3 : " << endl;
	string s2 = ">)]{()]<<<{})))>";
	cout << "������� ������ : " << s2 << endl;
	cout << "��������� : " << correct_bracket_seq(s2) << "\n\n";

	cout << "������ 4 : " << endl;
	string s3 = "<<<}}}][[])()(";
	cout << "������� ������ : " << s3 << endl;
	cout << "��������� : " << correct_bracket_seq(s3) << "\n\n";

	//task 12
	cout << "------------------------------TASK 12------------------------------\n\n";
	int a = 2;
	int sum = 1028;
	cout << "��� ������� ����� " << a << " ����� ������� ����� " << sum << " : ";
	for (auto x : efficient_expression_evaluation(a, sum))
		cout << x << " ; ";
	cout << "\n";
	a = 5;
	sum = 78780;
	cout << "��� ������� ����� " << a << " ����� ������� ����� " << sum << " : ";
	for (auto x : efficient_expression_evaluation(a, sum))
		cout << x << " ; ";
	cout << "\n";
	a = 2;
	sum = 16;
	cout << "��� ������� ����� " << a << " ����� ������� ����� " << sum << " : ";
	for (auto x : efficient_expression_evaluation(a, sum))
		cout << x << " ; ";
	cout << "\n";

	a = 7;
	sum = 282511320;
	cout << "��� ������� ����� " << a << " ����� ������� ����� " << sum << " : ";
	for (auto x : efficient_expression_evaluation(a, sum))
		cout << x << " ; ";
	cout << "\n";

	system("pause");
}