#pragma once
#include "Vector.h"

class Table {
private:
	Vector v; // Таблица клиентов
	T* current; // Указатель на первый свободный в таблице
public:
	Table(int s);
	~Table();
	T* begin();
	T* end();
	int length();
	int getSize();
	T* erase(T* pos);
	void clear();
	void resize(int plusSize);
	T* insert(const T& newClient);
	int input(T item);
	void output();
	void sort();
	int search(const T& tempClient);
	int replace(const T& oldClient, const T& newClient);
	int remove(const T& badClient);
};
