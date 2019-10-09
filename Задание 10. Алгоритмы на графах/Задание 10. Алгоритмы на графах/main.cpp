#include "matrix_graph.h"

enum Color { WHITE, GREY, BLACK };

void matrix_dfs_visit(const matrix_graph& m, int i, list<int>& q, Color* c)
{
	int N = m.get_max_vertexes();
	c[i] = GREY;
	for (int j = 0; j < N; j++) {
		if (i != j) {
			if (m.is_connected(i, j))
				if (c[j] == WHITE)
					matrix_dfs_visit(m, j, q, c);
				
		}
	}
	c[i] = BLACK;
	q.push_front(i);
}

void dfs(const matrix_graph& m, list<int>& visited_vertexes_in_order)
{
	int N = m.get_max_vertexes();
	Color* c = new Color[N];
	for (int i = 0; i < N; i++)
		c[i] = WHITE;
	for (int i = 0; i < N; i++)
		if (c[i] == WHITE)
			matrix_dfs_visit(m, i, visited_vertexes_in_order, c);
}

void print_scc(list<int>& l) {
	cout << "Strongly Connected Component:";
	for (list<int>::iterator iter = l.begin(); iter != l.end(); iter++)
		cout << " " << *iter;
	cout << "\n";
}

void dfs_transpose(matrix_graph& m, list<int>& visited_vertexes_in_order)
{
	int N = m.get_max_vertexes();
	Color* c = new Color[N];
	for (int i = 0; i < N; i++)
		c[i] = WHITE;

	for (list<int>::iterator iter = visited_vertexes_in_order.begin(); iter != visited_vertexes_in_order.end(); iter++) {
		int scc_head = *iter;
		if (c[scc_head] == WHITE) {
			list<int> scc;
			matrix_dfs_visit(m, scc_head, scc, c);
			print_scc(scc);
		}
	}
}


void get_strongly_connected_component(matrix_graph& m)
{
	list<int> visited_vertexes_in_order;
	dfs(m, visited_vertexes_in_order);
	m.reverse();
	dfs_transpose(m, visited_vertexes_in_order);
}

void main()
{

	vector<vector<int>> v = {
		{0,1,0,0,0,0,0},
		{0,0,1,1,0,0,0},
		{1,0,0,0,0,0,0},
		{0,0,0,0,1,0,0},
		{0,0,0,0,0,1,0},
		{0,0,0,1,0,0,1},
		{0,0,0,0,0,0,0}
	};
	
	matrix_graph m(v);
	get_strongly_connected_component(m);
	system("pause");
}