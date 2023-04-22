#include "MyString.h"
#define MAX_SIZE 256

// Конструктор по умолчанию
MyString::MyString() {
	/*
	len - длина массива = фактическое кол-во символов которое туда можно поместить включая \0
	cur - указывает на \0
	*/
	len = MAX_SIZE;
	cur = s = new char[len];
	*s = '\0';
}

// Конструктор от строки
MyString::MyString(const char* t) {
	s = new char[MAX_SIZE + strlen(t)];
	*s = '\0';
	strcpy_s(s, strlen(t) + 1, t);
	cur = &s[strlen(t)];
	len = MAX_SIZE + strlen(t);
}

// Конструктор копирования
MyString::MyString(const MyString& t) {
	s = new char[MAX_SIZE + t.len];
	*s = '\0';
	strcpy_s(s, strlen(t.s) + 1, t.s);
	cur = &s[strlen(t.s)];
	len = MAX_SIZE + t.len;
}

// Деструктор
MyString::~MyString() {
	delete[] s;
}

// Возвращает длину массива выделенного под строку
int MyString::length() {
	return len;
}

// Возвращает длину массива выделенного под строку
int MyString::length() const {
	return len;
}

// Создание копии объекта в динамической памяти
MyString* MyString::copy() {
	return new MyString(*this);
}

// Сравнение двух строк
int MyString::cmp(const MyString& t) {
	return strcmp(s, t.s);
}

// Ввод строки
int MyString::input(std::istream& cin) {
	if (cin.eof())
		return 0;

	char buf[MAX_SIZE];

	cin.getline(buf, MAX_SIZE - 2, '\n');
	if (strlen(buf) == 0)
		cin.getline(buf, MAX_SIZE - 2, '\n');

	s = new char[strlen(buf) + 1];

	len = MAX_SIZE + strlen(buf);
	*s = '\0';
	strcpy_s(s, strlen(buf) + 1, buf);
	cur = &s[strlen(buf)];
	return 0;
}

// Вывод строки на экран
int MyString::output(std::ostream& cout) {
	for (char* i = s; i < cur; i++)
		cout << *i;
	cout << std::endl;
	return 0;
}

// Начало новых функций

// Изменение размера строки
void MyString::resize(int newsize) {
	/*
	В newsize передаётся новый размер, а не то на сколько его надо увеличить
	*/
	char* new_s = new char[newsize];
	strcpy_s(new_s, strlen(s) + 1, s);
	delete[] s;
	s = new_s;
	cur = &s[strlen(s)];
}

// Возвращает истинный размер строки без учёта '\0'
int MyString::realSize() const {
	int count = 0;
	for (char* i = s; i != cur; i++)
		count++;
	return count;
}

// Поиск подстроки в строке
int MyString::find(int first, int last, const MyString& item) {
	/*
	fisrt, last - отражают ЧЕЛОВЕЧЕСКИЙ номер
	Ищет с позиции first по позицию last включительно
	*/

	// Проверка first и last на правильность, а строки-аргумента на существование
	if (first <= 0 || first > realSize() || last <= 0 || last > realSize() || first > last || item.realSize() == 0) {
		std::cout << "Error in find function, class MyString" << std::endl;
		return -2;
	}

	for (int i = first - 1; i < last; i++) {
		if (s[i] == item.s[0]) {
			bool flag = false;
			for (int j = i; j < item.realSize() + i; j++) {
				if (j > last - 1) {
					flag = true;
					break;
				}
				if (s[j] != item.s[j - i])
					flag = true;
			}
			if (!flag)
				return i;
		}
	}
	return -1;
}

// Формирование подстроки из строки
MyString MyString::substring(int pos, int count) {
	/*
	pos - отражает ЧЕЛОВЕЧЕСКИЙ номер
	count - сколько символов должно входить в подстроку
	pos = 1 -> формирование с первой позиции строки
	pos = len -> формирование подстроки из одного последнего элемента
	pos = len + 1 -> недопустимо
	*/

	MyString newString;
	char* buf = new char[5256];

	// Проверка pos и count на правильность
	if (pos <= 0 || pos > realSize() /*|| count > realSize() - pos - 1*/) {
		std::cout << "Error in substring function, class MyString" << std::endl;
		return newString; // Возврат пустой строки
	}

	int index = 0;
	for (int i = pos - 1; i < pos - 1 + count; i++) {
		buf[index] = s[i];
		index++;
	}
	buf[index] = '\0';

	MyString newString2(buf);

	return newString2;
}

// Удаление символов из строки
int MyString::erase(int pos, int count) {
	/*
	pos - отражает ЧЕЛОВЕЧЕСКИЙ номер
	pos = 1 -> удаление начиная с первого символа, включая первый символ
	pos = len -> удаление начиная с последнего символа, включая последний символ
	pos = len + 1 -> недопустимо
	count - число символов, которое будет стёрто
	*/

	// Проверка pos на правильность
	if (pos <= 0 || pos > realSize()) {
		std::cout << "Error in erase function, class MyString" << std::endl;
		return -1;
	}

	// Проверка count на правильность
	if (count < 0 || count > realSize()) {
		std::cout << "Error in erase function, class MyString" << std::endl;
		return -1;
	}

	char sym = s[pos - 1];
	int shift = 0;
	while (sym != '\0') {
		s[pos - 1 + shift] = s[pos - 1 + count + shift];
		shift++;
		sym = s[pos - 1 + shift];
	}

	cur -= count;

	return 0;
}

// Вставка строки на позицию
int MyString::insert(int pos, const MyString& item) {
	/*
	pos - отражает ЧЕЛОВЕЧЕСКИЙ номер
	pos = 1 -> вставка на первую позицию строки, вся строка сдвигается вправо
	pos = len -> вставка на предпоследнюю позицию строки, только последний символ сдвигается вправо
	pos = len + 1 -> вставка в самый конец строки, ничего не сдвигается
	*/

	// Проверка pos на правильность, а строки-аргумента на существование
	if (pos <= 0 || pos > len + 1 || item.realSize() == 0) {
		std::cout << "Error in insert function, class MyString" << std::endl;
		return -1;
	}

	int len1 = realSize();
	int len2 = item.realSize();

	// Проверка на наличие места для вставки в строке
	if (len1 + len2 + 1 > len)
		resize(len + item.len);

	// Вставка текста
	for (int i = len1 + len2; i != pos - 1; i--) {
		s[i] = s[i - len2];
	}
	for (int i = 0; i < len2; i++) {
		s[pos - 1 + i] = item.s[i];
	}

	cur = &s[len1 + len2];

	return 0;
}

// Удаление подстроки из строки
int MyString::remove(int first, int last, const MyString& item) {
	/*
	fisrt, last - отражают ЧЕЛОВЕЧЕСКИЙ номер
	Ищет для удаления с позиции first по позицию last включительно
	*/

	// Проверка first и last на правильность, а строки-аргумента на существование
	if (first <= 0 || first > realSize() || last <= 0 || last > realSize() || first > last || item.realSize() == 0) {
		std::cout << "Error in remove function, class MyString" << std::endl;
		return -1;
	}

	int index = find(first, last, item);

	if (index != -1) {
		int oldSize = realSize();
		for (int i = 0; i < item.realSize(); i++) {
			for (int j = index; s[j] != '\0'; j++)
				s[j] = s[j + 1];
			cur--;
		}
	}

	return 0;
}

// Замена подстроки в строке на другую подстроку
// заменить
int MyString::replace(int first, int last, const MyString& oldString, const MyString& newString) {
	/*
	fisrt, last - отражают ЧЕЛОВЕЧЕСКИЙ номер
	Ищет для замены с позиции first по позицию last включительно
	*/

	// Проверка first и last на правильность, а строк-аргументов на существование
	if (first <= 0 || first > realSize() || last <= 0 || last > realSize() || first > last || oldString.realSize() == 0 || newString.realSize() == 0) {
		std::cout << "Error in replace function, class MyString" << std::endl;
		return -1;
	}

	int index = find(first, last, oldString);

	if (index != -1) {
		remove(first, last, oldString);
		insert(index + 1, newString);
	}

	return 0;
}

// Разбивает строку на массив слов
MyString* MyString::split(int& count, char c) {
	count = 0;
	for (int i = 0; s[i] != '\0'; i++) {
		if (s[i] == c)
			count++;
	}
	count++;

	MyString* arr = new MyString[count];
	int index = 0, arrIndex = 0;

	char* buf = new char[len];
	char* cur = &buf[0];

	for (int j = 0; s[j] != '\0'; j++) {
		if (s[j] == c) {
			*cur = '\0';
			strcpy(arr[arrIndex].s, buf);
			arr[arrIndex].cur = &arr[arrIndex].s[strlen(buf)];
			arrIndex++;
			cur = &buf[0];
			continue;
		}
		*cur = s[j];
		cur++;
	}
	*cur = '\0';
	strcpy(arr[arrIndex].s, buf);
	arr[arrIndex].cur = &arr[arrIndex].s[strlen(buf)];

	delete[] buf;

	return arr;
}

// Разбивает строку на массив слов используя строку символов-разделителей
MyString* MyString::split(const MyString& splits, int& count) {
	int splitsSize = splits.realSize();

	// Проверка на существование строки с разделителями
	if (splitsSize == 0) {
		std::cout << "Error in split function, class MyString" << std::endl;
		return NULL;
	}

	MyString copy(*this);
	for (int i = 0; i < splitsSize; i++) {
		for (int j = 0; j < copy.realSize(); j++) {
			if (copy.s[j] == splits.s[i]) {
				copy.s[j] = ' ';
			}
		}
	}

	count = 0;
	for (int i = 0; copy.s[i] != '\0'; i++) {
		if (copy.s[i] == ' ')
			count++;
	}
	count++;

	MyString* arr = new MyString[count];
	int index = 0, arrIndex = 0;

	for (int i = 0; i < count; i++) {
		MyString temp;
		for (int j = index; copy.s[j] != ' ' && copy.s[j] != '\0'; j++) {
			char* t = new char[2];
			t[0] = copy.s[j];
			t[1] = '\0';
			MyString myChar(t);
			temp.insert(temp.realSize() + 1, myChar);
			delete[] t;
			index = j;
		}
		index += 2;
		arr[arrIndex] = temp;
		arrIndex++;
	}

	return arr;
}

// Соединение двух строк
MyString MyString::concate(const MyString& s1, const MyString& s2) {
	MyString my(s1);
	int len1 = s1.realSize();
	int len2 = s2.realSize();
	for (int i = 0; i <= len2; i++)
		my.s[len1 + i] = s2.s[i];

	my.cur = &my.s[len1 + len2];
	return my;
}

// Соединение массива строк
MyString MyString::concate(MyString* arr, int count) {
	MyString res;

	for (int i = 0; i < count; i++) {
		int len1 = res.realSize();
		int len2 = arr[i].realSize();
		for (int j = 0; j <= len2; j++)
			res.s[len1 + j] = arr[i].s[j];
		res.cur += len2;
	}

	return res;
}

// Соединение массива строк со вставкой символа разделителя
MyString MyString::join(MyString* arr, int count, char c) {
	MyString res;

	for (int i = 0; i < count; i++) {
		int len1 = res.realSize();
		int len2 = arr[i].realSize();
		for (int j = 0; j <= len2; j++)
			res.s[len1 + j] = arr[i].s[j];
		if (i != count - 1) {
			res.s[len1 + len2] = c;
			res.s[len1 + len2 + 1] = '\0';
			res.cur += len2 + 1;
		}
		else
			res.cur += len2;
	}

	return res;
}

// Перегрузка операторов

// Оператор присваивания
MyString& MyString::operator=(const MyString& t) {
	// Предотвращает удаление содержимого объекта при присваивании самому себе
	if (this == &t)
		return *this;

	delete[] s;
	s = new char[t.len + 1];
	strcpy_s(s, strlen(t.s) + 1, t.s);
	cur = &s[strlen(t.s)];
	len = t.len;

	return *this;
}

// Оператор преобразования типа из MyString в char*
MyString::operator char* () {
	/*
	Не указывается возвращаемое значение
	Имя совпадает с именем типа
	Отсутствуют аргументы
	Создание копии оставляет стринг s доступным только через интерфейс класса,
	защищая его от неправильного использования
	*/
	char* p = new char[len + 1];
	strcpy(p, s);
	return p;
}

// Оператор индексирования символов
char& MyString::operator[](int i) {
	if (i >= 0 && i < realSize())
		return s[i];
	std::cout << "Index error" << std::endl;
	exit(1);
}

// Оператор добавления в конец строки
MyString& MyString::operator+=(const MyString& t) {
	int len1 = realSize();
	int len2 = t.realSize();

	len = len + t.len;
	char* p = new char[len + 1];
	strcpy(p, s);
	strcat(p, t.s);
	delete[] s;
	s = p;
	cur = &s[len1 + len2 + 1];

	return *this;
}

// Оператор проверки на равенство
int operator==(MyString& a, MyString& b) {
	return !a.cmp(b);
}

// Оператор проверки на неравенство
int operator!=(MyString& a, MyString& b) {
	if (a.cmp(b) == 0)
		return 1;
	return 0;
}

// Оператор проверки на меньше
int operator<(MyString& a, MyString& b) {
	return a.cmp(b) < 0;
}

// Оператор проверки на меньше либо равно
int operator<=(MyString& a, MyString& b) {
	return a.cmp(b) <= 0;
}

// Оператор проверки на больше
int operator>(MyString& a, MyString& b) {
	return a.cmp(b) > 0;
}

// Оператор проверки на больше либо равно
int operator>=(MyString& a, MyString& b) {
	return a.cmp(b) >= 0;
}

// Оператор соединения двух строк
MyString operator+(const MyString& a, const MyString& b) {
	MyString tmp(a);
	tmp += b;
	return tmp;
}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, MyString& ms) {
	ms.output(os);
	return os;
}

// Оператор ввода
std::istream& operator>>(std::istream& is, MyString& ms) {
	ms.input(is);
	return is;
}
