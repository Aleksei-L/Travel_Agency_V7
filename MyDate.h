#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

typedef FILE* File;

class MyDate {
private:
	int day; // День
	int month; // Месяц
	int year; // Год
	static int daytab[2][13]; // Кол-во дней в месяцах
	static const char* MonthName[13]; // Названия месяцев
	static const char* DayNames[8]; // Названия дней недели
public:
	MyDate();
	MyDate(int d, int m, int y);
	MyDate(char* s);
	MyDate(const MyDate&);
	~MyDate();
	int getDay();
	int getDay() const;
	int getMonth();
	int getMonth() const;
	int getYear();
	int getYear() const;
	char* getDayOfWeek() const;
	void setDay(int d);
	void setMonth(int m);
	void setYear(int y);
	void addDays(long d);
	void addMonth(long m);
	void addYears(long y);
	int validate();
	static int isYearLeap(int y);
	unsigned long toLong() const;
	char* toChar();
	static int dayOfYear(int y, int m, int d);
	static void dayOfMonth(int d, int y, int* m, int* dd);
	MyDate parser(char*);
	void dispose();
	MyDate* copy();
	int	equal(const MyDate& t) const;
	int	cmp(const MyDate& t) const;
	int	input(std::istream& cin = std::cin);
	void output(std::ostream& cout = std::cout) const;
	// Перегрузка операторов
	MyDate& operator = (const MyDate str);
	operator const char* ();
	friend std::ostream& operator << (std::ostream&, const MyDate&);
	friend std::istream& operator >> (std::istream&, MyDate&);
	friend int operator == (const MyDate&, const MyDate&);
	friend int operator != (const MyDate&, const MyDate&);
	friend int operator <= (const MyDate&, const MyDate&);
	friend int operator >= (const MyDate&, const MyDate&);
	friend int operator < (const MyDate&, const MyDate&);
	friend int operator > (const MyDate&, const MyDate&);
	MyDate& operator += (long);
	friend MyDate operator + (const MyDate&, long d);
	friend long operator - (const MyDate&, const MyDate&);
	MyDate& operator ++ ();
	MyDate operator ++ (int);
	MyDate& operator -- ();
	MyDate operator -- (int);
};
