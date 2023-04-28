#pragma once
#include <iostream>
#include "MyString.h"
#include "MyDate.h"

class Client {
private:
	MyString name; // Имя клиента
	MyString city; // Адрес клиента
	int phone; // Телефон клиента
	double age; // Возраст клиента
	MyDate birth; // Дата рождения клиента
public:
	Client();
	Client(const char* n, const char* c, int p, int a, int d, int m, int y);
	Client(const Client& t);
	void dispose();
	~Client();
	int	input(std::istream& cin = std::cin);
	void output(std::ostream& cout = std::cout) const;
	int cmp(const Client& t) const;
	int equal(const Client& t) const;
	Client* copy();
	// Перегрузка операторов
	friend int operator == (const Client&, const Client&);
	friend int operator != (const Client&, const Client&);
	friend int operator < (const Client&, const Client&);
	friend int operator <= (const Client&, const Client&);
	friend int operator > (const Client&, const Client&);
	friend int operator >= (const Client&, const Client&);
	friend std::ostream& operator << (std::ostream&, const Client&);
	friend std::istream& operator >> (std::istream&, Client&);
};

typedef Client* T; // Теперь таблица работает с абстрактным типом T
