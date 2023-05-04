#pragma once
#include "Vector.h"

class Table {
private:
	Vector v; // Таблица клиентов
	T buf; // Буфер для промежуточного хранения клиента
	T* current; // Указатель на первый свободный в таблице
public:
	Table();
	Table(int s, T b);
	~Table();
	T* begin() const;
	T* end() const;
	int length();
	int getSize();
	T* erase(T* pos);
	void clear();
	void resize(int plusSize);
	T* insert(const T& newClient);
	int input(std::istream& cin);
	void output(std::ostream& cout) const;
	void sort();
	int search(const T& tempClient);
	int replace(const T& oldClient, const T& newClient);
	int remove(const T& badClient);
	// Перегрузка операторов
	friend std::ostream& operator << (std::ostream& os, const Table& r);
	friend std::istream& operator >> (std::istream& is, Table& r);
};
