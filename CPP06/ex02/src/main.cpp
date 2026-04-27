#include <cstdlib>
#include <iostream>
#include <ostream>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base* generate() {
	int ran = std::rand() % 3;
	switch (ran) {
		case 0:
			std::cout << "Generated: A\n";
			return new A();
		case 1:
			std::cout << "Generated: B\n";
			return new B();
		case 2:
			std::cout << "Generated: C\n";
			return new C();
		default:
			return NULL;
	}
}

void identify(Base* p) {
	if (dynamic_cast<A*>(p))
		std::cout << "Pointer Type: A\n";
	else if (dynamic_cast<B*>(p))
		std::cout << "Pointer Type: B\n";
	else if (dynamic_cast<C*>(p))
		std::cout << "Pointer Type: C\n";
	else
		std::cout << "Pointer Type: Unknown\n";
}

void identify(Base& p) {
	try {
		A& a = dynamic_cast<A&>(p);
		std::cout << "Reference Type: A\n";
		(void)a;
		return;
	} catch (...) {}

	try {
		B& b = dynamic_cast<B&>(p);
		std::cout << "Reference Type: B\n";
		(void)b;
		return;
	} catch (...) {}

	try {
		C& c = dynamic_cast<C&>(p);
		std::cout << "Reference Type: C\n";
		(void)c;
		return;
	} catch (...) {}

	std::cout << "Reference Type: Unknown\n";
}
int main()
{
	std::srand(time(0));
	Base* ptr = generate();
	Base* bad_ptr = new Base;

	std::cout << "===Good===" << std::endl;
	identify(ptr);
	identify(*ptr);

	std::cout << "===Bad===" << std::endl;
	identify(bad_ptr);
	identify(*bad_ptr);

	delete ptr;
	delete bad_ptr;
	return 0;
}

