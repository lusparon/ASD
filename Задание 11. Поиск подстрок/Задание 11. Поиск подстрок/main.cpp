#include "search_subs.h"

void main()
{
	setlocale(LC_ALL, "Rus");
	time_t start = clock();
	string f = "war-peace.txt";
	string p = "delicious";
	cout << "Индекс первого вхождения \"" << p << "\" в файл \"" << f << "\" : " << getFirstEntry(f,p) << endl;
	cout.precision(10);
	cout << "время : " << double(clock() - start) / CLOCKS_PER_SEC << " сек" << "\n\n";

	time_t start1 = clock();
	string f1 = "Master and Margarita.txt";
	string p1 = "love";
	cout << "Индекс первого вхождения \"" << p1 << "\" в файл \"" << f1 << "\" : " << getFirstEntry(f1, p1) << endl;
	cout.precision(10);
	cout << "время : " << double(clock() - start1) / CLOCKS_PER_SEC << " сек" << "\n\n";

	time_t start2 = clock();
	string f2 = "Lord_of_the_rings.txt";
	string p2 = "Frodo";
	cout << "Индекс первого вхождения \"" << p2 << "\" в файл \"" << f2 << "\" : " << getFirstEntry(f2, p2) << endl;
	cout.precision(10);
	cout << "время : " << double(clock() - start2) / CLOCKS_PER_SEC << " сек" << "\n\n";
	
	time_t start3 = clock();
	string f3 = "Video_Games.csv";
	string p3 = "game";
	cout << "Индекс первого вхождения \"" << p3 << "\" в файл \"" << f3 << "\" : " << getFirstEntry(f3, p3) << endl;
	cout.precision(10);
	cout << "время : " << double(clock() - start3) / CLOCKS_PER_SEC << " сек" << "\n\n";

	system("pause");
}
