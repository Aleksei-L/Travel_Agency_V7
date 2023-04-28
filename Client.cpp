#include "Client.h"
#include <string.h>

// Конструктор клиента по умолчанию
Client::Client() {
	phone = 0;
	age = 0.0;
}

// Конструктор клиента с заданными параметрами полей
Client::Client(const char* n, const char* c, int p, int a, int d, int m, int y) :name(n), city(c), phone(p), age(a), birth(d, m, y) {
}

// Конструктор копирования
Client::Client(const Client& t) : name(t.name), city(t.city), phone(t.phone), age(t.age), birth(t.birth) {
}

// Освобождение памяти из-под клиента
void Client::dispose() {
}

// Деструктор клиента
Client::~Client() {
	dispose();
}

// Ввод информации про клиента
int Client::input(std::istream& cin) {
	std::cout << "Enter client name: ";
	cin >> name;
	bool b = cin.eof();
	if (b)
		return 0;

	std::cout << "Enter city: ";
	cin >> city;

	std::cout << "Enter phone: ";
	cin >> phone;

	std::cout << "Enter age: ";
	cin >> age;

	std::cout << "Enter birth's day, month and year:" << std::endl;
	cin >> birth;

	return 1;
}

// Вывод информации про клиента
void Client::output(std::ostream& cout) const {
	cout << "Client name: " << name << std::endl;
	cout << "City: " << city << std::endl;
	cout << "Phone: " << phone << std::endl;
	cout << "Age: " << age << std::endl;
	cout << "Birth day: " << birth << std::endl;
}

// Разница между клиентами
int Client::cmp(const Client& b) const {
	int cond;
	if ((cond = name.cmp(b.name)) != 0)
		return cond;
	else if ((cond = city.cmp(b.city)) != 0)
		return cond;
	else if ((cond = phone - b.phone) != 0)
		return cond;
	else if ((cond = age - b.age) != 0)
		return cond;
	else if ((cond = birth.cmp(b.birth)))
		return cond;
	return 0;
}

// Проверка клиентов на равенство
int Client::equal(const Client& t) const {
	return !name.cmp(t.name) && !city.cmp(t.city) && (phone == t.phone) && (age == t.age) && !birth.cmp(t.birth);
}

// Создание копии объекта в динамической памяти
Client* Client::copy() {
	return new Client(*this);
}

// Перегрузка операторов

// Оператор проверки на равенство
int operator == (const Client& a, const Client& b) {
	return !a.cmp(b);
}

// Оператор проверки на неравенство
int operator != (const Client& a, const Client& b) {
	if (a.cmp(b) != 0)
		return 1;
	return 0;
}

// Оператор проверки на меньшесть
int operator < (const Client& a, const Client& b) {
	return a.cmp(b) < 0;
}

// Оператор проверки на меньшесть либо равенство
int operator <= (const Client& a, const Client& b) {
	return a.cmp(b) <= 0;
}

// Оператор проверки на большесть
int operator > (const Client& a, const Client& b) {
	return a.cmp(b) > 0;
}

// Оператор проверки на большесть либо равенство
int operator >= (const Client& a, const Client& b) {
	return a.cmp(b) >= 0;
}

// Оператор вывода
std::ostream& operator << (std::ostream& os, const Client& r) {
	r.output(os);
	return os;
}

// Оператор ввода
std::istream& operator >> (std::istream& is, Client& r) {
	r.input(is);
	return is;
}
