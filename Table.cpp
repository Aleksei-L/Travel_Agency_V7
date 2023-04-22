#include "Table.h"
#include <algorithm>

// Конструктор таблицы
Table::Table(int s): v(s) {
	current = v.begin();
}

// Деструктор таблицы
Table::~Table() {
	clear();
}

// Возвращает указатель на первый элемент таблицы
T* Table::begin() {
	return v.begin();
}

// Возвращает указатель на первый свободный элемент таблицы
T* Table::end() {
	return current;
}

// Возвращает размер заполненной части таблицы
int Table::length() {
	return current - v.begin();
}

// Возвращает общий размер таблицы
int Table::getSize() {
	return v.getSize();
}

// Удаление одного элемента в таблице (по индексу)
T* Table::erase(T* pos) {
	(*pos)->dispose();
	for (T* i = pos; i < end(); i++)
		*i = *(i + 1);
	current--;
	return pos;
}

// Удаление всех элементов в таблице
void Table::clear() {
	for (T* i = begin(); i < current; i++) {
		(*i)->dispose();
		delete (*i);
	}
	current = begin();
}

// Увеличение размера таблицы на plusSize элементов
void Table::resize(int plusSize) {
	if (plusSize <= 0) {
		std::cout << "Wrong size!" << std::endl;
		return;
	}
	v.resize(plusSize);
}

// Вставка нового клиента в таблицу
T* Table::insert(const T& newClient) {
	if (length() < v.getSize())
		*current++ = newClient->copy();
	return current;
}

// Ввод таблицы
int Table::input(T item) {
	int count;
	if (length() == getSize()) {
		std::cout << "Size over, enter new size: ";
		int newSize;
		std::cin >> newSize;
		resize(newSize * 2);
	}
	for (count = 0; length() != getSize(); count++) {
		if (!item->input())
			break;
		insert(item);
	}
	return count;
}

// Вывод таблицы
void Table::output() {
	bool flag = false;
	int counter = 1;
	for (T* i = begin(); i != end(); i++) {
		std::cout << "Client #" << counter++ << std::endl;
		(*i)->output();
		flag = true;
		std::cout << std::endl;
	}
	if (!flag)
		std::cout << "There is no to output!" << std::endl;
}

// Сортировка таблицы
void Table::sort() {
	for (int i = 0; i < getSize(); i++) {
		for (int j = i + 1; j < getSize(); j++) {
			if (v.item(i)->cmp(*v.item(j)) > 0)
				std::swap(v.item(i), v.item(j));
		}
	}
}

// Поиск клиента в таблице, возвращает индекс найденного клиента или -1 если клиент не найден
int Table::search(const T& tempClient) {
	for (T* i = begin(); i < end(); i++) {
		if ((*i)->equal(*tempClient))
			return i - begin();
	}
	return -1;
}

// Замена клиента в таблице
int Table::replace(const T& oldClient, const T& newClient) {
	int counter = 0;
	for (T* i = begin(); i < end(); i++) {
		if ((*i)->equal(*oldClient)) {
			(*i)->dispose();
			(*i) = (newClient)->copy();
			counter++;
		}
	}
	return counter;
}

// Удаление всех вхождений
int Table::remove(const T& badClient) {
	T* i = begin();
	int n = 0;
	for (T* j = begin(); j < end(); j++) {
		if (!(*j)->equal(*badClient)) {
			*i++ = *j;
		}
		else {
			(*j)->dispose();
			n++;
		}
	}
	current = i;
	return n;
}
