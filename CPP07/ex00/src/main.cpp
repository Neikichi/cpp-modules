#include <iostream>
#include "Whatever.hpp"

template <typename T>
void printWhatever(T& a, T& b) {
	std::cout << "Before Swap a: " << a << ", b: " << b << std::endl;
	std::cout << "Before Min : " << ::min(a, b) << std::endl;
	std::cout << "Before Max : " << ::max(a, b) << std::endl;
	::swap(a, b);
	std::cout << "After Swap a: " << a << ", b: " << b << std::endl;
	std::cout << "After Min : " << ::min(a, b) << std::endl;
	std::cout << "After Max : " << ::max(a, b) << std::endl;

}

int main() {
	std::cout << "===Int===" << std::endl;
	int ia = 42;
	int ib = -42;
	printWhatever(ia, ib);

	std::cout << "===Char===" << std::endl;
	char ca = 'K';
	char cb = 'L';
	printWhatever(ca, cb);

	std::cout << "===String===" << std::endl;
	std::string sa = "Kuala";
	std::string sb = "Lumpur";
	printWhatever(sa, sb);

	std::cout << "===Float===" << std::endl;
	float fa = 3.14f;
	float fb = 0.42f;
	printWhatever(fa, fb);

	std::cout << "===Double===" << std::endl;
	double da = 3.14;
	double db = 0.42;
	printWhatever(da, db);

	return 0;
}
