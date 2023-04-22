//#include "Table.h"
//
//int main() {
//	int size, code, position;
//	std::cout << "Enter Table's size: ";
//	std::cin >> size;
//	Table myT(size);
//	Client first, second;
//
//	while (true) {
//		std::cout << "Select the program operation mode:" << std::endl;
//		std::cout << "1) Input table" << std::endl;
//		std::cout << "2) Output table" << std::endl;
//		std::cout << "3) Sort table" << std::endl;
//		std::cout << "4) Search client in table" << std::endl;
//		std::cout << "5) Erase client from table" << std::endl;
//		std::cout << "6) Remove client from table" << std::endl;
//		std::cout << "7) Replace client in table" << std::endl;
//		std::cout << "10) Exit" << std::endl;
//		std::cin >> code;
//		switch (code) {
//		case 1:
//			std::cout << std::endl;
//			myT.input(&first);
//			std::cout << std::endl;
//			break;
//		case 2:
//			std::cout << std::endl;
//			myT.output();
//			std::cout << std::endl;
//			break;
//		case 3:
//			std::cout << std::endl;
//			myT.sort();
//			std::cout << std::endl;
//			break;
//		case 4:
//			std::cout << std::endl;
//			std::cout << "Enter client for Search:" << std::endl;
//			first.input();
//			std::cout << "Client's index: " << myT.search(&first) << " (-1 if not founded)" << std::endl;
//			std::cout << std::endl;
//			break;
//		case 5:
//			std::cout << std::endl;
//			std::cout << "Enter position(client's number) for Erase:" << std::endl;
//			std::cin >> position;
//			myT.erase(myT.begin() + position - 1);
//			std::cout << std::endl;
//			break;
//		case 6:
//			std::cout << std::endl;
//			std::cout << "Enter client for Remove:" << std::endl;
//			first.input();
//			myT.remove(&first);
//			std::cout << std::endl;
//			break;
//		case 7:
//			std::cout << std::endl;
//			std::cout << "Enter old client for Replace:" << std::endl;
//			first.input();
//			std::cout << "Enter new client for Replace:" << std::endl;
//			second.input();
//			myT.replace(&first, &second);
//			std::cout << std::endl;
//			break;
//		case 10:
//			return 0;
//		default:
//			std::cout << std::endl;
//			std::cout << "Unknown command" << std::endl;
//			std::cout << std::endl;
//		}
//	}
//}
#include "MyString.h"

int main() {
	MyString str1, str2, str3;
	

	

	return 0;
}
