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
	int input();
	void output();
	int cmp(const Client& t);
	int equal(const Client& t);
	Client* copy();
};

typedef Client* T; // Теперь таблица работает с абстрактным типом T
