#include "Vector.h"

// Конструктор по умолчанию
Vector::Vector() {
	v = new T[size = 10];
}

// Конструктор с задаваемым размером вектора
Vector::Vector(int sz) {
	v = new T[size = sz];
}

// Конструктор копирования
Vector::Vector(const Vector& l) {
	v = new T[size = l.size];
	for (int i = 0; i < size; i++)
		v[i] = l.v[i];
}

// Деструктор вектора
Vector::~Vector() {
	delete[] v;
}

// Возвращает указатель на начало вектора
T* Vector::begin() const {
	return v;
}

// Возвращает указатель на конец вектора
T* Vector::end() const {
	return v + size;
}

// Возвращает размер вектора
int Vector::getSize() {
	return size;
}

// Получение элемента из вектора
T& Vector::item(int it) {
	if (it < 0 || it > size) {
		std::cout << "Index error" << std::endl;
		exit(1);
	}
	return v[it];
}

// Изменение размера вектора
void Vector::resize(int n) {
	if (n < size) {
		std::cout << "Resize error in Vector class" << std::endl;
		return;
	}
	T* t = new T[n];
	for (int i = 0; i < size; i++)
		t[i] = v[i];
	delete[] v;
	v = t;
	size = n;
}

// Перегрузка операторов
T& Vector::operator [] (int i) {
	if (i >= 0 && i < size)
		return v[i];
	std::cout << "Index error" << std::endl;
	exit(1);
}
