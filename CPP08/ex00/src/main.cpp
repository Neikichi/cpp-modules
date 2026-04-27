#include "EasyFind.hpp"
#include <exception>
#include <iostream>
#include <vector>
#include <list>

template <typename T>
void dummyPush(T& con) {
	int val = rand() % 10;
	std::cout
		<< "dummyPush of: " << val << std::endl;
	for (int i = 0; i < val; i++) {
		con.push_back(i);
	}
	typename T::iterator it = con.begin();
	for (int i = 0; it != con.end(); it++, i++) {
		std::cout
			<< "Container[" << i
			<< "]: '" << *it << "'" << std::endl;
	}
	std::cout << std::endl;
}

template <typename T>
void testRun(T& con) {
	typename T::iterator it;
	try {
		int val = rand() % 10;
		std::cout
			<< "LF: " << val << std::endl;
		it = easyfind(con, val);
		std::cout
			<< "Found: " << *it << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

int main() {
	std::vector<int> vInt;
	std::list<int> lInt;

	srand(time(0));

	dummyPush(vInt);
	dummyPush(lInt);

	std::cout << "===TestRun===\n";
	testRun(vInt);
	testRun(lInt);
}
