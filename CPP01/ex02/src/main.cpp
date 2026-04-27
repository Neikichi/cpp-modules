#include <iostream>

int main() {
	std::string str = "HI THIS IS BRAIN";
	std::string *strPtr = &str;
	std::string &strRef = str;

	std::cout << "Memory address of str variable		: " << &str << "\n";
	std::cout << "Memory address of strPtr variable	: " << strPtr << "\n";
	std::cout << "Memory address of strRef variable	: " << &strRef << "\n";

	std::cout << "Value of str variable		: " << str << "\n";
	std::cout << "Value of strPtr variable	: " << *strPtr << "\n";
	std::cout << "Value of strRef variable	: " << strRef << "\n";

	return 0;
}
