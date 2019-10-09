#include <iostream>
#include <fstream>
#include <queue>
#include <istream>
#include <map>
#include <algorithm>
#include "HPQueue.h"
#include <string>
#include <functional>
#include <sstream>
#include <unordered_map>

using namespace std;
//task1-2
struct Mypair
{
private:
	std::pair<std::string, int> data;
public:
	Mypair(std::pair<std::string, int> s) : data(s)
	{}

	int length()
	{
		return data.first.length();
	}

	int count()
	{
		return data.second;
	}

	friend bool operator > (Mypair ms1, Mypair ms2)
	{
		return ms1.count() > ms2.count();
	}

	friend bool operator < (Mypair ms1, Mypair ms2)
	{
		return ms1.count() < ms2.count();
	}

	bool isName()
	{
		char c = *(data.first.begin());
		return c > 'A'&& c < 'Z';
	}


	friend std::ostream& operator<<(std::ostream& os, const Mypair& ms)
	{
		os << ms.data.first<< ", "<< ms.data.second<< " вхождений\n";
		return os;
	}
	
};

//task 3
bool is_anagram(string s1, string s2)
{
	int n = s1.length();
	if (n == s2.length())
	{
		sort(s1.begin(),s1.end());
		sort(s2.begin(), s2.end());
		for (int i = 0; i < n; i++)
			if (s1[i] != s2[i])
				return false;
	}
	else return false;
	return true;
}

// task 4
struct Game {
	string name, platform, genre, publisher, developer, rating;
	int release_year;
	double na_sales, eu_sales, jp_sales, other_sales, global_sales;
	int critic_score, critic_count, user_score, user_count;
	/*friend ostream& operator<<(ostream& os, Game& g) {
		return os << g.name << "|" << g.platform << "|" << g.release_year << "|" << g.genre << "|" << g.publisher
			<< "|" << g.na_sales << "|" << g.eu_sales << "|" << g.jp_sales << "|" << g.other_sales << "|" <<
			g.global_sales << "|" << g.critic_score << "|" << g.critic_count << "|" << g.user_score << "|" <<
			g.user_count << "|" << g.developer << "|" << g.rating << endl;
	}*/
};

vector<Game> parse_database(string database_filename)
{
	vector<Game> games;
	ifstream ifile(database_filename);
	string str;
	int i = 2;
	try
	{
		if (getline(ifile, str))
			while (getline(ifile, str))
			{
				//if (i == 3350)
					//break;
				++i;
				istringstream iss(str);
				Game g;
				string ss;
				getline(iss, ss, ',');
				g.name = ss;
				getline(iss, ss, ',');
				g.platform = ss;
				getline(iss, ss, ',');
				if (ss == "" || ss == "N/A") {
					g.release_year = -1;
				}
				else {
					g.release_year = stoi(ss);
				}
				getline(iss, ss, ',');
				g.genre = ss;
				getline(iss, ss, ',');
				g.publisher = ss;
				getline(iss, ss, ',');
				if (ss == "") {
					g.na_sales = -1;
				}
				else {
					g.na_sales = stod(ss);
				}
				getline(iss, ss, ',');
				if (ss == "") {
					g.eu_sales = -1;
				}
				else {
					g.eu_sales = stod(ss);
				}
				getline(iss, ss, ',');
				if (ss == "") {
					g.jp_sales = -1;
				}
				else {
					g.jp_sales = stod(ss);
				}
				getline(iss, ss, ',');
				if (ss == "") {
					g.other_sales = -1;
				}
				else {
					g.other_sales = stod(ss);
				}
				getline(iss, ss, ',');
				if (ss == "") {
					g.global_sales = -1;
				}
				else {
					g.global_sales = stod(ss);
				}
				getline(iss, ss, ',');
				if (ss == "") {
					g.critic_score = -1;
				}
				else {
					g.critic_score = stoi(ss);
				}
				getline(iss, ss, ',');
				if (ss == "") {
					g.critic_count = -1;
				}
				else {
					g.critic_count = stoi(ss);
				}
				getline(iss, ss, ',');
				if (ss == "" || ss == "tbd") {
					g.user_score = -1;
				}
				else {
					g.user_score = stoi(ss);
				}
				getline(iss, ss, ',');
				if (ss == "") {
					g.user_count = -1;
				}
				else {
					g.user_count = stoi(ss);
				}
				getline(iss, ss, ',');
				g.developer = ss;
				getline(iss, ss, ',');
				g.rating = ss;
				games.push_back(g);
			}
	}
	catch (...) {}
	return games;
}

// task 4
map<string, map<string, double>> publishers_income(vector<Game>& games)
{
	map<string, map<string, double>> res;
	for (Game game : games)
	{
		if (game.global_sales > 0.000001)
			res[game.publisher][game.genre] += game.global_sales;
	}
	
	return res;
}

// task 5
map<int, map<string, int>> best_genre(vector<Game>& games)
{
	map<int, map<string, int>> res;
	for (Game game : games)
	{
		if (game.global_sales > 0.000001 && game.release_year != -1)
			res[game.release_year][game.genre] += game.global_sales;
	}
	return res;
}

//task6
map<string, map<int, string>> best_developers(vector<Game>& games)
{
	map<string, map<int, string>> res;
	unordered_map<string, unordered_map<string, int>> temp;
	for (Game game : games)
	{
		if (game.global_sales > 0.00000001 && game.developer != "" && game.publisher != "")
			temp[game.publisher][game.developer] += game.global_sales;
	}
	for (auto x : temp)
	{
		for (auto y : x.second)
			res[x.first][y.second] = y.first;
	}
	return res;
}

void main()
{
    setlocale(LC_ALL, "Russian");
	map<string, int> mm;
	string data;

	ifstream in("Lord_of_the_rings.txt");
	while (in >> data)
		mm[data] ++;

	//task1
	HPQueue<Mypair> pq;
	for (auto cur = mm.begin(); cur != mm.end(); cur++)
		pq.add(Mypair((*cur)));
	cout << "---------------------------------------task1---------------------------------------\n";
	cout << "40 наиболее часто встречающихся слов : \n";
	for (int i = 0; i < 40; i++)
	{
		cout << pq.extractMax();
		pq.pop();
	}
	cout << "\n\n";

	HPQueue<Mypair> pq1;
	for (auto cur = mm.begin(); cur != mm.end(); cur++)
		pq1.add(Mypair((*cur)));

	//task2
	cout << "---------------------------------------task2---------------------------------------\n";
	cout << "20 наиболее часто встречающихся собственных имён : \n";
	int i = 0;
	while (i != 20)
	{
		if (pq1.extractMax().isName())
		{
			cout << pq1.extractMax();
			pq1.pop();
			i++;
		}
		pq1.pop();
	}

	//task3
	vector<vector<string>> l;
	vector<string> words;
	for (auto cur = mm.begin(); cur != mm.end(); cur++)
		words.push_back((*cur).first);

	for (int i = 0; i < words.size(); i++)
	{
		if (words[i] != "")
		{
			vector<string> group;
			for (int j = i + 1; j < words.size(); j++)
			{
				if (is_anagram(words[i], words[j]))
				{
					group.push_back(words[j]);
					words[j] = "";
				}
			}
			if (group.size() != 0)
			{
				group.push_back(words[i]);
				words[i] = "";
				l.push_back(group);
			}
		}
	}
    //все аннограммы
	/*for (auto x : l)
	{
		for (auto y : x)
			cout << y << " ; ";
		cout << "\n";
	}*/
		
	int max = 0;
	int ind;
	for (int i = 0 ; i < l.size();i++)
		if (l[i].size() > max)
		{
			max = l[i].size();
			ind = i;
		}
	cout << "---------------------------------------task3---------------------------------------\n";
	cout << "Самая большая группа анаграмм : \n";
	for (auto x : l[ind])
		cout << x << " ; ";
	cout << "\n\n";

	int max1 = 0;
	int ind1;
	for (int i = 0; i < l.size(); i++)
		if (l[i][0].length() > max1)
		{
			max1 = l[i][0].length();
			ind1 = i;
		}
	cout << "Самые длинные анаграммы : \n";
	for (auto x : l[ind1])
		cout << x << " ; ";
	cout << "\n\n";

	// task 4
	cout << "---------------------------------------task4---------------------------------------\n";
	cout << "Суммарный доход по различным жанрам игр для каждого издателя : \n";
	vector<Game> gamesDB = parse_database("Video_Games.csv");
	map<string, map<string, double>> pubs_income = publishers_income(gamesDB);
	for (auto x : pubs_income) {
		cout << x.first << ":\n";
		for (auto y : x.second) {
			cout << "    " << y.first << " = " << y.second << endl;
		}
	}
	cout << "\n\n";

	// task 5
	cout << "---------------------------------------task5---------------------------------------\n";
	cout << "Наиболее доходный жанр игровой индустрии по каждому году : \n";
	map<int, map<string, int>> profit_genre = best_genre(gamesDB);
	for (auto x : profit_genre) {
		cout << x.first << ":\n";
		string profitable_genre = "";
		int max = INT_MIN;
		for (auto y : x.second) {
			if (y.second > max) {
				max = y.second;
				profitable_genre = y.first;
			}
		}
		if (max != INT_MIN) {
			cout << " " << profitable_genre << endl;
		}
	}
	cout << "\n\n";

	// task6
	cout << "---------------------------------------task6---------------------------------------\n";
	cout << "5 наиболее доходных разработчиков для каждого издателя : \n";
	map<string, map<int, string>> profit_devs = best_developers(gamesDB);
	for (auto x : profit_devs) {
		cout << x.first << ":\n";
		int i = 0;
		for (auto it = x.second.crbegin(); it != x.second.crend() && i < 5; ++it, ++i) {
			cout << "  " << i + 1 << ':' << (*it).second << "\n";
		}
	}

    system("pause");
}

