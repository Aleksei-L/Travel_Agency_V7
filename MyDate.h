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
	char* getDayOfWeek();
	MyDate getNow();
	void setDay(int d);
	void setMonth(int m);
	void setYear(int y);
	void addDays(long d);
	void addMonth(long m);
	void addYears(long y);
	int validate();
	static int isYearLeap(int y);
	unsigned long toLong();
	char* toChar();
	static int dayOfYear(int y, int m, int d);
	static void dayOfMonth(int d, int y, int* m, int* dd);
	MyDate parser(char*);
	void assign(const MyDate& t);
	void dispose();
	MyDate* copy();
	int equal(const MyDate& t);
	int	cmp(const MyDate& t);
	int	input(File fp);
	int	input();
	int	output(File fp);
	int output();
};
