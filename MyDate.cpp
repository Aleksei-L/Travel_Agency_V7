#include "MyDate.h"

int MyDate::daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};
const char* MyDate::MonthName[13] = { "Wrong month", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
const char* MyDate::DayNames[8] = { "Wrong day", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

// Конструктор по умолчанию
MyDate::MyDate() {
	day = month = year = 0;
}

// Конструктор от 3 чисел
MyDate::MyDate(int d, int m, int y) {
	day = d;
	month = m;
	year = y;
	if (!validate())
		std::cout << " Error validate MyDate" << std::endl;
}

// Конструктор от строки
MyDate::MyDate(char* s) {
	char* days = new char[3];
	char* months = new char[3];
	char* years = new char[5];

	days[0] = s[0];
	days[1] = s[1];
	days[2] = '\0';
	day = atoi(days);

	months[0] = s[3];
	months[1] = s[4];
	months[2] = '\0';
	month = atoi(months);

	years[0] = s[6];
	years[1] = s[7];
	years[2] = s[8];
	years[3] = s[9];
	years[4] = '\0';
	year = atoi(years);

	if (!validate()) {
		day = 0;
		month = 0;
		year = 0;
	}
}

// Конструктор копирования
MyDate::MyDate(const MyDate& d) {
	day = d.day;
	month = d.month;
	year = d.year;
}

// Деструктор
MyDate::~MyDate() {
	dispose();
}

// Возвращает день
int MyDate::getDay() {
	return day;
}

// Возвращает день
int MyDate::getDay() const {
	return day;
}

// Возвращает месяц
int MyDate::getMonth() {
	return month;
}

// Возвращает месяц
int MyDate::getMonth() const {
	return month;
}

// Возвращает год
int MyDate::getYear() {
	return year;
}

// Возвращает год
int MyDate::getYear() const {
	return year;
}

// Возвращает день недели соответствующий дате
char* MyDate::getDayOfWeek() const {
	long dd = (toLong()) % 7 + 1;
	char* s = new char[strlen(DayNames[dd]) + 1];
	strcpy(s, DayNames[dd]);
	return s;
}

// Присваивание дня
void MyDate::setDay(int d) {
	int tmp = day;
	day = d;
	if (!validate())
		day = tmp;
}

// Присваивание месяца
void MyDate::setMonth(int m) {
	int tmp = month;
	month = m;
	if (!validate())
		month = tmp;
}

// Присваивание года
void MyDate::setYear(int y) {
	int tmp = year;
	year = y;
	if (!validate())
		year = tmp;
}

// Добавление произвольного кол-ва дней к годам экземпляра (аргумент может быть отрицательным числом)
void MyDate::addDays(long d) {
	if (d > 0) {
		while (d--) {
			day++;
			if (day > daytab[isYearLeap(year)][month]) {
				day = 1;
				month++;
				if (month == 13)
					month = 1; year++;
			}
		}
	}
	else {
		while (d++) {
			day--;
			if (!day) {
				month--;
				if (!month) {
					month = 12;
					year--;
					if (!year) {
						year = 1;
						month = 1;
						day = 1;
						return;
					}
				}
				day = daytab[isYearLeap(year)][month];
			}
		}
	}
}

// Добавление произвольного кол-ва месяцев к годам экземпляра (аргумент может быть отрицательным числом)
void MyDate::addMonth(long m) {
	if (m > 0)
		while (m--) {
			month++;
			if (month == 13) {
				month = 1;
				year++;
			}
		}
	else {
		while (m++) {
			month--;
			if (!month) {
				month = 12; year--;
				if (!year) {
					year = 1;
					month = 1;
					return;
				}
			}
		}
	}
	int k;
	if (day > (k = daytab[isYearLeap(year)][month]))
		day = k;
}

// Добавление произвольного кол-ва лет к годам экземпляра (аргумент может быть отрицательным числом)
void MyDate::addYears(long y) {
	year += y;
	if (year <= 0) {
		year = 1;
		month = 1;
		day = 1;
	}
	int k = daytab[isYearLeap(year)][month];
	if (day > k)
		day = k;
}

// Валидация даты
int MyDate::validate() {
	return (year > 0 && month > 0 && month <= 12 && day > 0 && day <= daytab[isYearLeap(year)][month]);
}

// Проверка года на високосность
int MyDate::isYearLeap(int y) {
	return ((!(y % 4)) && (y % 100) || (!(y % 400)));
}

// Перевод даты в число
unsigned long MyDate::toLong() const {
	unsigned long d, m, y;
	d = day;
	y = 1;
	m = 1;
	while (y < year) {
		d += 365 + isYearLeap(y);
		y++;
	}
	while (m < month) {
		d += daytab[isYearLeap(year)][m];
		m++;
	}
	return d;
}

// Перевод даты в строку
char* MyDate::toChar() {
	char s[256], buf[256], * s1;
	s[0] = '\0';
	_itoa(day, buf, 10);
	strcat(s, buf);
	strcat(s, ".");
	_itoa(month, buf, 10);
	strcat(s, buf);
	strcat(s, ".");
	_itoa(year, buf, 10);
	strcat(s, buf);
	s1 = new char[strlen(s) + 1];
	strcpy(s1, s);
	return s1;
}

// Возвращает число даты в году
int MyDate::dayOfYear(int y, int m, int d) {
	int dd = d;
	while (--m)
		dd += daytab[isYearLeap(y)][m];
	return dd;
}

// Возвращает число даты в месяце
void MyDate::dayOfMonth(int d, int y, int* m, int* dd) {
	*m = 1;
	while (d > daytab[isYearLeap(y)][*m])
		d -= daytab[isYearLeap(y)][(*m)++];
	*dd = d;
	return;
}

// Парсинг строки с датой
MyDate MyDate::parser(char* s) {
	return MyDate(s);
}

// Освобождение памяти из-под экземпляра класса
void MyDate::dispose() {}

// Создание копии объекта в динамической памяти
MyDate* MyDate::copy() {
	return new MyDate();
}

// Проверка дат на равенство
int	MyDate::equal(const MyDate& d) const {
	return day == d.day && month == d.month && year == d.year;
}

// Сравнение двух дат
int	MyDate::cmp(const MyDate& d) const {
	if (year != d.year)
		return year - d.year;
	else if (month != d.month)
		return month - d.month;
	else
		return day - d.day;
}

// Ввод даты
int MyDate::input(std::istream& cin) {
	std::cout << "Day: ";
	cin >> day;
	std::cout << "Month: ";
	cin >> month;
	std::cout << "Year: ";
	cin >> year;
	if (!validate()) {
		std::cout << "Error Data" << std::endl;
		return day = month = year = 0;
	}
	return 1;
}

// Вывод даты
void MyDate::output(std::ostream& cout) const {
	const char* s = MonthName[month], * ss = getDayOfWeek();
	cout << day << " (" << ss << ") " << s << " (" << month << ") " << year;
}

// Перегрузка операторов

// Оператор присваивания
MyDate& MyDate::operator = (const MyDate dt) {
	day = dt.day;
	month = dt.month;
	year = dt.year;
	return *this;
}

// Оператор преобразования типа из MyDate в char *
MyDate::operator const char* () {
	return "MyDate";
}

// Оператор вывода
std::ostream& operator << (std::ostream& out, const MyDate& other) {
	other.output(out);
	return out;
}

// Оператор ввода
std::istream& operator >> (std::istream& in, MyDate& other) {
	other.input(in);
	return in;
}

// Оператор проверки на равенство
int operator == (const MyDate& d1, const MyDate& d2) {
	return d1.day == d2.day && d1.month == d2.month && d1.year == d2.year;
}

// Оператор проверки на неравенство
int operator != (const MyDate& d1, const MyDate& d2) {
	return d1.day != d2.day || d1.month != d2.month || d1.year != d2.year;
}

// Оператор проверки на меньшесть либо равенство
int operator <= (const MyDate& d1, const MyDate& d2) {
	return d1.cmp(d2) < 0 || d1.cmp(d2) == 0;
}

// Оператор проверки на большесть либо равенство
int operator >= (const MyDate& d1, const MyDate& d2) {
	return d1.cmp(d2) > 0 || d1.cmp(d2) == 0;
}

// Оператор проверки на меньшесть
int operator < (const MyDate& d1, const MyDate& d2) {
	return d1.cmp(d2) < 0;
}

// Оператор проверки на большесть
int operator > (const MyDate& d1, const MyDate& d2) {
	return d1.cmp(d2) > 0;
}

// Оператор сложения с присваиванием
MyDate& MyDate::operator += (long d) {
	addDays(d);
	return *this;
}

// Оператор сложения
MyDate operator + (const MyDate& dt, long d) {
	MyDate Dt;
	Dt = dt;
	Dt += d;
	return Dt;
}

// Оператор вычитания
long operator - (const MyDate& d1, const MyDate& d2) {
	return d1.toLong() - d2.toLong();
}

// Префиксный оператор инкремента
MyDate& MyDate::operator ++ () {
	*this += 1;
	return *this;
}

// Постфиксный оператор инкремента
MyDate MyDate::operator ++ (int) {
	MyDate ret(*this);
	*this += 1;
	return ret;
}

// Префиксный оператор декремента
MyDate& MyDate::operator -- () {
	*this += -1;
	return *this;
}

// Постфиксный оператор декремента
MyDate MyDate::operator -- (int) {
	MyDate ret(*this);
	*this += -1;
	return ret;
}
