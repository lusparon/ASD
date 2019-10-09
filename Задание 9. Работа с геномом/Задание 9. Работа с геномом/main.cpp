#include "funcs.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	setlocale(LC_ALL,"RUSSIAN");
	cout << editDistance("anthropology", "anthologies") << endl;
	cout << longestSubstring("anthropology", "anthologies") << endl;
	map<int, string> nations;
	nations[0] = "Chinese";
	nations[1] = "American";
	nations[2] = "Ethiopian";
	nations[3] = "Yakutian";
	nations[4] = "Italian";

	string ACGT[5];
	fstream f1("Chinese.txt");	
	f1 >> ACGT[0];
	fstream f2("NativeAmerica.txt");
	f2 >> ACGT[1];
	fstream f3("Ethiopia.txt");
	f3 >> ACGT[2];
	fstream f4("Yakut.txt");
	f4 >> ACGT[3];
	fstream f5("Italian.txt");
	f5 >> ACGT[4];



	auto al = new int* [5];
	for (int i = 0; i < 5; i++)
		al[i] = new int[5];

	for (int i = 0; i < 5; i++)
	{
		for (int j = i + 1; j < 5; j++)
		{
			auto res = maxAlignment(ACGT[i], ACGT[j]);
			al[i][j] = res;
			al[j][i] = res;
		}
	}

	cout << "Italian DNA and Chinese DNA: " << al[4][0] << endl;
	cout << "Yakut DNA and Ethiop DNA:    " << al[3][2] << endl;

	cout << "Italian people:" << endl;	
	int maxInd = 0;
	int minInd = 0;	
	for (int i = 0; i < 4; i++)
	{		
		if (al[4][i] > al[4][maxInd])
			maxInd = i;		
		if (al[4][i] < al[4][minInd])
			minInd = i;	
	}
	cout << "  Most similar DNA: " << nations[maxInd] << endl;
	cout << "  Least similar DNA:" << nations[minInd] << endl;

	/*pair<int, int> maxInds(0, 0);
	pair<int, int> minInds(0, 0);
	for (int i = 0; i < 5; i++)
	{
		for (int j = i + 1; j < 5; j++)
		{
			if (al[i][j] > al[maxInds.first][maxInds.second])
				maxInds = pair<int, int>(i, j);
			if (al[i][j] < al[maxInds.first][maxInds.second])
				minInds = pair<int, int>(i, j);
		}
	}
	cout << "  Most similar DNA between " << nations[maxInds.first] << " and " << nations[maxInds.second] << "people" << endl;
	cout << "  Least similar DNA between " << nations[minInds.first] << " and " << nations[minInds.second] << "people" << endl;*/
}