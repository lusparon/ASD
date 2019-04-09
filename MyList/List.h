#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <iterator>
#include <list>
#include <algorithm>
#include <ctime>
#include <vector>
#include <assert.h>
using namespace std;

template<typename T>
class node
{
public:
	node<T> * next, * prev;
	T data;

	node(T x)
	{
		this->next = nullptr;
		this->prev = nullptr;
		this->data = x;
	}
	node(node<T>* prev, T x, node<T>* next)
	{
		next = next;
		prev = prev;
		data = x;
	}
};

template<typename T>
class list_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
	node<T> * p;
public:
	list_iterator(node<T>* pp) : p(pp) {}

	T& operator*()
	{
		return p->data;
	}

	list_iterator<T> operator++()
	{
		p = p->next;
		return *this;
	}

	list_iterator<T> operator--()
	{
		p = p->prev;
		return *this;
	}

	template <typename T1>
	friend bool operator != (list_iterator<T1> it1, list_iterator<T1> it2)
	{
		return it1.p != it2.p;
	}

	template <typename T1>
	friend bool operator == (list_iterator<T1> it1, list_iterator<T1> it2)
	{
		return !(it1 != it2);
	}
};



template<typename T>
class Mylist
{
	node<T> * first, * last;
public:
	Mylist()
	{
		void * place = operator new(sizeof(node<T>));
		node<T> *head = static_cast<node<T> *>(place);
		head->next = head;
		head->prev = head;
		first = head;
		last = head;
	}
	Mylist(T x)
	{
		void * place = operator new(sizeof(node<T>));
		node<T> *fict = static_cast<node<T> *>(place);
		node<T> *head = new node<T>(fict, x, fict);
		fict->next = head;
		fict->prev = head;
		first = last = head;
	}
	void push_back(T x)
	{
		last->next->data = x;
		last = last->next;
		void * place = operator new(sizeof(node<T>));
		node<T> *fict = static_cast<node<T> *>(place);
		fict->next = first;
		fict->prev = last;
		last->next = fict;
		first->prev = fict;
	}

	


	Mylist(std::initializer_list<T> il)
	{
		first = node<T>(il.begin());
		auto p = next(il.begin());
		while (p != il.end())
		{
			push_back(*p++);
		}
	}
	list_iterator<T> begin() 
	{
		return list_iterator<T>(first);
	}
	list_iterator<T> end() 
	{
		return list_iterator<T>(last->next);
	}
	

	friend std::ostream & operator<< (std::ostream & os, Mylist<T>& l)
	{
		list_iterator<int> li = l.begin();
		do {
			os << *li << " ";
			++li;
		} while (li != l.end());
		return os;
	}

	//Задание 4
	void reverse()
	{
		node<T>* ln = first;
		node<T>* fn = first;
		do {
			swap(ln->next, ln->prev);
			ln = ln->prev;
		} while (ln != last);
		swap(ln->next, ln->prev);
		last = fn;
		first = ln;
	}
};

//Задание 1
int countPositive(Mylist<int>& l);

//Задание 2
void maxElCount(int& maxEl, int& count, Mylist<int>& l);

//Задание 3
void splitLists(Mylist<int>& in, Mylist<int>& neg, Mylist<int>& pos);

//Создание списка 
Mylist<int> create_intmylist(initializer_list<int> lst);

#endif LIST_H


