#pragma once
#include "Client.h"

class Vector {
private:
	T* v; // Массив для хранения объектов вектора (сам вектор)
	int size; // Размер вектора
public:
	Vector();
	Vector(int sz);
	Vector(const Vector&);
	~Vector();
	T* begin();
	T* end();
	int getSize();
	T& item(int);
	void resize(int);
};
