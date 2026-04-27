#include <climits>
#include <cstdlib>
#include <iostream>
#include "Span.hpp"

template <typename T>
void printContainer(const T& c) {
	if (c.empty())
		throw std::runtime_error("printContainer error: empty container");
	typename T::const_iterator it = c.begin();

	std::cout << "===Print Container===\n";
	for (size_t i = 0; it != c.end(); ++it, ++i) {
		std::cout
			<< "Container[" << i + 1 << "]: "
			<< *it << std::endl;
	}
}

void tryRun(const Span& sp) {
	try {
		printContainer(sp);
		std::cout << std::endl;
		std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest Span: " << sp.longestSpan() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl;
}

int main() {
	Span sp = Span(5);

	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	tryRun(sp);

	// ===========================
	Span randSp = Span(10000);

	randSp.autoRandElement(UINT_MAX);
	tryRun(randSp);


	return 0;
}
