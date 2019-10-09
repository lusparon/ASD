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

	//������� ������ ������
	if (patternLen > textLen) {
		return -1;
	}

	//������� ��������, ������������� 
	unordered_map<char,int> offsetTable;
	for (int i = 0; i <= 255; i++) 
	{
		offsetTable[(char)i] = patternLen;
	}

	//���������� ������� �������� 
	for (int i = 0; i < patternLen - 1; i++) 
	{
		offsetTable[pattern[i]] = patternLen - i - 1;
	}

	int i = patternLen - 1;
	int j = i;
	int k = i;

	//������ �� �����
	while (j >= 0 && i <= textLen - 1) 
	{
		j = patternLen - 1;
		k = i;
		while (j >= 0 && text[k] == pattern[j]) //��������� 
		{
			k--;
			j--;
		}
		i += offsetTable[text[i]];
	}

	//���� ����� �� ������ ������ ������� ������ ����� �������, �� ����� ��������� ���
	if (k >= textLen - patternLen) 
	{
		return -1;
	}
	else {
		return k + 1;
	}
}
