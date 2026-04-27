#include <iostream>
#include "Iter.hpp"

void printInt(const int& n) {
	std::cout << "const int: " << n << std::endl;
}

void printStr(std::string& s) {
	s += "!";
	std::cout << "string: " << s << std::endl;
}

template <typename T>
void printTemplates(T& t) {
	std::cout << "Generic template print: " << t << std::endl;
}

int main() {
	const int nums[] = {1, 2, 3};
	int n[] = {7, 6, 5};
	std::string words[] = {"hi", "hello", "world"};

	iter(nums, 3, printInt);
	iter(words, 3, printStr);
	iter(n, 3, printTemplates<int>);
	iter(nums, 3, printTemplates<const int>);
}
