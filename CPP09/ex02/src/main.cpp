#include "PmergeMe.hpp"
#include <exception>
#include <iostream>

std::string avjoin(int ac, char **av) {
	std::string s;
	for (int i = 1; i < ac; i++) {
		s += av[i];
		if (i != ac - 1)
			s += " ";
	}
	return s;
}

int main(int ac, char **av) {
	if (ac < 2) {
		std::cerr << "Invalid input! Usage: ./PmergeMe <elements of positive value>" << std::endl;
		return 1;
	}
	
	std::string s = avjoin(ac, av);
	PmergeMe mi;

	try {
		mi.run(s);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
