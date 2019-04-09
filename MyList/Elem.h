#ifndef ELEM_H
#define ELEM_H
#include "List.h"

class elem {
	int data;
public:
	/// ���������� ������������ � ��������� �������� ������
	static size_t assigns, compares;
	/// ����������� - ������������� ��������� ���������
	elem() {
		data = rand();
	};
	/// ���������� �����������
	elem(const elem & other) : data(other.data) {
		++assigns;
	};
	/// ����� ���������
	static void reset() {
		assigns = 0;
		compares = 0;
	}
	/// ���������� �������� ��������� - ��� ���������� ����������
	bool operator<(const elem &other) const {
		++compares;
		return data < other.data;
	}
	/// ���������� ��������� ������������
	const elem &operator=(const elem &other) {
		++assigns;
		data = other.data;
		return *this;
	}
	/// ������������� ������� - �������� "��������� � �����"
	friend std::ostream & operator<<(std::ostream & out, const elem & item);
};

// ������������� ����������� ����� ������
size_t elem::assigns = 0;
size_t elem::compares = 0;

/// ���������� �������� ������ � ����� - ��� ������������� �������
std::ostream & operator<<(std::ostream & out, const elem & item) {
	return out << item.data;
}
#endif ELEM_H

