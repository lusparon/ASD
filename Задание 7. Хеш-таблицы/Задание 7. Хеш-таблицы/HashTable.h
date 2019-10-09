#ifndef HASH_TABLE
#define HASH_TABLE
#include <iostream>
#include <list>

const int T_S = 2000;
using namespace std;
struct HashNode {
	int k,v;
	HashNode* n;
	HashNode(int k, int v) {
		this->k = k;
		this->v = v;
		this->n = NULL;
	}
public:
	void print()
	{
		cout << "              Key : " << k << " ; Value : " << v << "\n";
		if (this->n != NULL)
			this->n->print();
	}
};
class HashTable {
public:
	HashNode** ht;
	HashTable() 
	{
		ht = new HashNode * [T_S];
		for (int i = 0; i < T_S; i++)
			ht[i] = NULL;
	}
	int HashFunc(int key) 
	{
		const double A = 0.6180339887;
		return T_S * fmod(key * A, 1);
	}
	void Insert(int k, int v = 0) 
	{
		int hash_i = HashFunc(k);
		HashNode* p = NULL;
		HashNode* en = ht[hash_i];
		while (en != NULL) 
		{
			if (en->k != k)
			{
				p = en;
				en = en->n;
			}
			else if (en->k == k) break;
		}
		if (en == NULL) 
		{
			en = new HashNode(k, v);
			if (p == NULL) {
				ht[hash_i] = en;
			}
			else {
				p->n = en;
			}
		}
	}
	void Remove(int k) 
	{
		int hash_v = HashFunc(k);
		HashNode* en = ht[hash_v];
		HashNode* p = NULL;
		if (en == NULL || en->k != k) {
			//cout << "No Element found at key " << k << endl;
			return;
		}
		while (en->n != NULL) {
			p = en;
			en = en->n;
		}
		if (p != NULL) {
			p->n = en->n;
		}
		delete en;
		//cout << "Element Deleted" << endl;
	}
	bool SearchKey(int k) {
		int hash_v = HashFunc(k);
		bool flag = false;
		HashNode* en = ht[hash_v];
		if (en != NULL) {
			while (en != NULL) {
				if (en->k == k) {
					flag = true;
				}
				if (flag) {
					//cout << "Element found at key " << k << ": ";
					//cout << en->v << endl;
					return true;
				}
				en = en->n;
			}
		}
		if (!flag)
		{
			//cout << "No Element found at key " << k << endl;
			return false;
		}
	}
	~HashTable() {
		delete[] ht;
	}

	void print()
	{
		for (int i = 0; i < T_S; i++)
			if (ht[i] != NULL)
			{
				cout << "Hash-Index : " << i << " : \n";
				ht[i]->print();
			}
	}


};


#endif HASH_TABLE

