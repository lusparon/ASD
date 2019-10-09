#pragma once
#include <iostream>
#include <list>
#include <vector>
using namespace std;

class matrix_graph
{
private:
	vector<vector<int>> vertexes;
public:
	template <typename Iterator>
	matrix_graph(Iterator begin, Iterator end)
	{
		vector<int> v(begin, end);
		for (size_t i = 0; i < v.size(); ++i) {
			vertexes.push_back(v);
		}
	}
	matrix_graph(vector<vector<int>> v)
	{
		vector<int> vv(v.size());
		for (size_t i = 0; i < vv.size(); ++i) {
			vertexes.push_back(vv);
		}
		for (size_t i = 0; i < v.size() ; i++)
			for (size_t j = 0; j < v[i].size(); j++)
				vertexes[i][j] = v[i][j];
	}

	void reverse()
	{
		for (int i = 0; i < vertexes.size(); i++)
			for (int j = 0; j < vertexes[i].size(); j++)
			{
				if (vertexes[i][j] == 1 && vertexes[j][i] == 0) {
					vertexes[j][i] = -1;
					vertexes[i][j] = 0;
				}
			}

		for (int i = 0; i < vertexes.size(); i++)
			for (int j = 0; j < vertexes[i].size(); j++)
			{
				if (vertexes[i][j] == -1)
					vertexes[i][j] = 1;
			}
	}

	int get_max_vertexes() const
	{
		return vertexes.size();
	}

	bool is_connected(int i, int j) const
	{
		return (vertexes[i][j] == 1);
	}
};