#pragma once
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <stack>
#include <assert.h>
#include <cmath>
#include <list>
#include <queue>
using namespace std;

//task 17
//wts - массив весов, cost - массив стоимостей предметов, W - вместимость рюкзака
//массив dp собственно реализует динамическое программирование
//функция возвращает максимальную стоимость, которую можно набрать
int knapsack(const vector<int>& wts, const vector<int>& cost, int W)
{
	assert(wts.size() == cost.size());
	size_t n = wts.size();
	vector<vector<int> > dp(W + 1, vector<int>(n + 1, 0));
	for (size_t i = 1; i <= n; i++)
	{
		for (int w = 1; w <= W; w++)
		{
			if (wts[i - 1] <= w)
			{
				dp[w][i] = max(dp[w][i - 1], dp[w - wts[i - 1]][i - 1] + cost[i - 1]);
			}
			else
			{
				dp[w][i] = dp[w][i - 1];
			}
		}
	}
	return dp[W][n];
}

//task2
string correct_bracket_seq(string s)
{
	stack <int> p;
	string res = "";
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '(' || s[i] == '{' || s[i] == '[' || s[i] == '<') 
		{
			p.push(s[i]);
			res += s[i];
		}
		else {
			if (s[i] == ')' && !p.empty())
				if (p.top() == '(')
				{
					p.pop();
					res += ')';
				}
				else res += "[]";
			else
				if (s[i] == '}' && !p.empty())
					if (p.top() == '{')
					{
						p.pop();
						res += '}';
					}
					else res += "{}";
				else
					if (s[i] == ']' && !p.empty())
						if (p.top() == '[')
						{
							p.pop();
							res += ']';
						}
						else res += "[]";
					else 
						if (s[i] == '>' && !p.empty())
							if (p.top() == '<')
							{
								p.pop();
								res += '>';
							}
							else res += "<>";
						else 
							if ((s[i] == '}' || s[i] == ')' || s[i] == ']' || s[i] == '>') && p.empty())
								switch (s[i])
								{
								case '}':
									res += "{}";
									break;
								case ')':
									res += "()";
									break;
								case ']':
									res += "[]";
									break;
								case '>':
									res += "<>";
									break;
								}
		}
	}
	while (!p.empty())
	{
		switch (p.top())
		{
		case '{':
			res += "}";
			break;
		case '(':
			res += ")";
			break;
		case '[':
			res += "]";
			break;
		case '<':
			res += ">";
			break;
		}
		p.pop();
	}
	return res;
}

//task 12
vector<int> efficient_expression_evaluation(int a, int sum)
{
	vector<int> sv;;
	vector<int> res;
	int s = 0;
	int deg = 0;
	while (pow(a, deg) < sum)
	{
		sv.insert(sv.begin(), deg);
		deg++;
	}

	if (pow(a, deg) == sum)
	{
		res.push_back(deg);
		return res;
	}
	for (int i = 0; i < sv.size(); i++)
	{
		if (s + pow(a,sv[i]) < sum)
		{
			res.push_back(sv[i]);
			s += pow(a, sv[i]);
		}
		else if (s + pow(a, sv[i]) == sum)
		{
			res.push_back(sv[i]);
			return res;
		}
	}

	return res;
}
