#include "Table.h"
#include <algorithm>

// Конструктор по умолчанию
Table::Table() : v(10), buf(0) {
	current = v.begin();
}

// Конструктор с заданными значениями полей
Table::Table(int s, T b) : v(s), buf(b) {
	current = v.begin();
}

// Деструктор таблицы
Table::~Table() {
	clear();
}

// Возвращает указатель на первый элемент таблицы
T* Table::begin() const {
	return v.begin();
}

// Возвращает указатель на первый свободный элемент таблицы
T* Table::end() const {
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

// Изменение размера таблицы на plusSize элементов
void Table::resize(int plusSize) {
	int temp = length();
	v.resize(plusSize);
	current = &v[v.getSize() - temp];
}

// Вставка нового клиента в таблицу
T* Table::insert(const T& newClient) {
	if (length() < v.getSize())
		*current++ = newClient->copy();
	return current;
}

// Ввод таблицы
int Table::input(std::istream& cin) {
	int count = 0;
	if (length() == getSize()) {
		std::cout << "Size over, enter new size: ";
		int newSize;
		std::cin >> newSize;
		resize(newSize);
	}
	for (int i = length(); i < getSize(); i++) {
		if (!buf->input(std::cin))
			break;
		insert(buf);
	}
	return count;
}

// Вывод таблицы
void Table::output(std::ostream& cout) const {
	bool flag = false;
	int counter = 1;
	for (T* i = begin(); i != end(); i++) {
		std::cout << "Client #" << counter++ << std::endl;
		(*i)->output(cout);
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
			if (*v[i] > *v[j])
				std::swap(v[i], v[j]);
		}
	}
}

// Поиск клиента в таблице, возвращает индекс найденного клиента или -1 если клиент не найден
int Table::search(const T& tempClient) {
	for (T* i = begin(); i < end(); i++) {
		if (**i == *tempClient)
			return i - begin();
	}
	return -1;
}

// Замена клиента в таблице
int Table::replace(const T& oldClient, const T& newClient) {
	int counter = 0;
	for (T* i = begin(); i < end(); i++) {
		if (**i == *oldClient) {
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
		if (**j != *badClient) {
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

// Перегрузка операторов

// Оператор вывода
std::ostream& operator << (std::ostream& os, const Table& r) {
	r.output(os);
	return os;
}

// Оператор ввода
std::istream& operator >> (std::istream& is, Table& r) {
	r.input(is);
	return is;
}
