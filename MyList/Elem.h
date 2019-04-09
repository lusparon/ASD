#ifndef ELEM_H
#define ELEM_H
#include "List.h"

class elem {
	int data;
public:
	/// Количество присваиваний и сравнений объектов класса
	static size_t assigns, compares;
	/// Конструктор - инициализация случайным значением
	elem() {
		data = rand();
	};
	/// Копирующий конструктор
	elem(const elem & other) : data(other.data) {
		++assigns;
	};
	/// Сброс счетчиков
	static void reset() {
		assigns = 0;
		compares = 0;
	}
	/// Перегрузка операции сравнения - для сортировок достаточно
	bool operator<(const elem &other) const {
		++compares;
		return data < other.data;
	}
	/// Перегрузка оператора присваивания
	const elem &operator=(const elem &other) {
		++assigns;
		data = other.data;
		return *this;
	}
	/// Дружественная функция - операция "поместить в поток"
	friend std::ostream & operator<<(std::ostream & out, const elem & item);
};

// Инициализация статических полей класса
size_t elem::assigns = 0;
size_t elem::compares = 0;

/// Перегрузка операции вывода в поток - как дружественная функция
std::ostream & operator<<(std::ostream & out, const elem & item) {
	return out << item.data;
}
#endif ELEM_H

