#pragma once
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

int editDistance(string s1, string s2, int insCost = 1, int delCost = 1, int replCost = 1)
{
	int l1 = s1.length();
	int l2 = s2.length();
	auto d = new int* [l1 + 1];
	for (int i = 0; i < l1 + 1; i++)
		d[i] = new int[l2 + 1];	
	
	d[0][0] = 0;
	for (int i = 1; i < l2 + 1; i++)
		d[0][i] = d[0][i - 1] + insCost;
	for (int i = 1; i < l1 + 1; i++)
	{
		d[i][0] = d[i - 1][0] + delCost;
		for (int j = 1; j < l2 + 1; j++)
		{			
			if (s1[i - 1] == s2[j - 1])
				d[i][j] = d[i - 1][j - 1];
			else
				d[i][j] = min({
					d[i - 1][j] + delCost,
					d[i][j - 1] + insCost,
					d[i - 1][j - 1] + replCost });
		}
	}

	auto result = d[l1][l2];
	for (int i = 0; i < l1 + 1; i++)
		delete d[i];
	return result;
}

int longestSubstring(string s1, string s2)
{
	int l1 = s1.length();
	int l2 = s2.length();
	auto d = new int* [l1 + 1];
	for (int i = 0; i < l1 + 1; i++)
		d[i] = new int[l2 + 1];

	d[0][0] = 0;
	for (int i = 1; i < l2 + 1; i++)
		d[0][i] = 0;
	for (int i = 1; i < l1 + 1; i++)
	{
		d[i][0] = 0;
		for (int j = 1; j < l2 + 1; j++)
		{
			if (s1[i - 1] == s2[j - 1])
				d[i][j] = d[i - 1][j - 1] + 1;
			else
				d[i][j] = max(
					d[i - 1][j],
					d[i][j - 1]);
		}
	}

	auto result = d[l1][l2];
	for (int i = 0; i < l1 + 1; i++)
		delete d[i];
	return result;
}

int maxAlignment(string s1, string s2)
{
	auto replCosts = new int* [4];		
	replCosts[0] = new int[4]{ 10, -1, -3, -4 };
	replCosts[1] = new int[4]{ -1, 7, -5, -3 };
	replCosts[2] = new int[4]{ -3, -5, 9, 0 };
	replCosts[3] = new int[4]{ -4, -3, 0, 8 };
	map<char, int> conv;
	conv['A'] = 0;
	conv['G'] = 1;
	conv['C'] = 2;
	conv['T'] = 3;
	int insCost = -5;
	int delCost = -5;

	int l1 = s1.length();
	int l2 = s2.length();
	auto d = new int* [l1 + 1];
	for (int i = 0; i < l1 + 1; i++)
		d[i] = new int[l2 + 1];

	d[0][0] = 0;
	for (int i = 1; i < l2 + 1; i++)
		d[0][i] = d[0][i - 1] + insCost;
	for (int i = 1; i < l1 + 1; i++)
	{
		d[i][0] = d[i - 1][0] + delCost;
		for (int j = 1; j < l2 + 1; j++)
		{			
			auto c1 = conv[s1[i]];
			auto c2 = conv[s2[j]];
			d[i][j] = max({
				d[i - 1][j] + delCost,
				d[i][j - 1] + insCost,
				d[i - 1][j - 1] + replCosts[c1][c2]});
		}
	}

	auto result = d[l1][l2];
	for (int i = 0; i < l1 + 1; i++)
		delete d[i];
	return result;
}

