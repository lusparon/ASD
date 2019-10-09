#pragma once
#include<iostream>
#include<fstream>
#include<unordered_map>
#include<string>
#include<functional>
#include<algorithm>
#include<chrono>
#include<intrin.h>

using namespace std;

string ReadFile(string f_path)
{
	fstream fs(f_path);
	string res = "";
	string s = "";
	while (fs)
	{
		getline(fs, s);
		res += s;
	}
	fs.close();
	return res;
}

int getFirstEntry(string f, string pattern) 
{
	string text = ReadFile(f);
	int textLen = text.length();
	int patternLen = pattern.length();

	//ќбразец больше строки
	if (patternLen > textLen) {
		return -1;
	}

	//“аблица смешений, инициализаци€ 
	unordered_map<char,int> offsetTable;
	for (int i = 0; i <= 255; i++) 
	{
		offsetTable[(char)i] = patternLen;
	}

	//«аполнение таблицы смешений 
	for (int i = 0; i < patternLen - 1; i++) 
	{
		offsetTable[pattern[i]] = patternLen - i - 1;
	}

	int i = patternLen - 1;
	int j = i;
	int k = i;

	//ѕроход по слову
	while (j >= 0 && i <= textLen - 1) 
	{
		j = patternLen - 1;
		k = i;
		while (j >= 0 && text[k] == pattern[j]) //Ёвристика 
		{
			k--;
			j--;
		}
		i += offsetTable[text[i]];
	}

	//≈сли число на выходе больше размера строки минус образец, то такой подстроки нет
	if (k >= textLen - patternLen) 
	{
		return -1;
	}
	else {
		return k + 1;
	}
}
