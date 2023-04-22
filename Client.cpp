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
int Client::input() {
	std::cout << "Enter client name: ";
	std::cin >> name;

	std::cout << "Enter city: ";
	std::cin >> city;

	std::cout << "Enter phone: ";
	std::cin >> phone;

	std::cout << "Enter age: ";
	std::cin >> age;

	std::cout << "Enter birth's day, month and year: ";
	birth.input();

	return !std::cin.eof();
}

// Вывод информации про клиента
void Client::output() {
	std::cout << "Client name: " << name << std::endl;
	std::cout << "City: " << city << std::endl;
	std::cout << "Phone: " << phone << std::endl;
	std::cout << "Age: " << age << std::endl;
	std::cout << "Birth day:";
	birth.output();
}

// Разница между клиентами
int Client::cmp(const Client& b) {
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
int Client::equal(const Client& t) {
	return !name.cmp(t.name) && !city.cmp(t.city) && (phone == t.phone) && (age == t.age) && !birth.cmp(t.birth);
}

// Создание копии объекта в динамической памяти
Client* Client::copy() {
	return new Client(*this);
}
