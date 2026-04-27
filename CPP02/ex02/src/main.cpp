#include "Fixed.hpp"
#include <iostream>

int main() {
	std::cout << "\n=== Basic Tests ===\n";
	Fixed a;
	Fixed const b(Fixed(5.05f) * Fixed(2));

	std::cout << "a: " << a << std::endl;
	std::cout << "++a: " << ++a << std::endl;
	std::cout << "a after ++a: " << a << std::endl;
	std::cout << "a++: " << a++ << std::endl;
	std::cout << "a after a++: " << a << std::endl;
	std::cout << "b: " << b << std::endl;
	std::cout << "max(a, b): " << Fixed::max(a, b) << std::endl;

	std::cout << "\n=== Arithmetic Tests ===\n";
	Fixed x(3.5f);
	Fixed y(1.25f);

	std::cout << "x: " << x << ", y: " << y << std::endl;
	std::cout << "x + y = " << (x + y) << std::endl;
	std::cout << "x - y = " << (x - y) << std::endl;
	std::cout << "x * y = " << (x * y) << std::endl;
	std::cout << "x / y = " << (x / y) << std::endl;

	std::cout << "\n=== Comparison Tests ===\n";
	std::cout << std::boolalpha;
	std::cout << "x == y: " << (x == y) << std::endl;
	std::cout << "x != y: " << (x != y) << std::endl;
	std::cout << "x > y:  " << (x > y) << std::endl;
	std::cout << "x < y:  " << (x < y) << std::endl;
	std::cout << "x >= y: " << (x >= y) << std::endl;
	std::cout << "x <= y: " << (x <= y) << std::endl;

	std::cout << "\n=== min / max Tests ===\n";
	std::cout << "min(x, y): " << Fixed::min(x, y) << std::endl;
	std::cout << "max(x, y): " << Fixed::max(x, y) << std::endl;

	const Fixed cx(42.0f);
	const Fixed cy(42.5f);
	std::cout << "min(const): " << Fixed::min(cx, cy) << std::endl;
	std::cout << "max(const): " << Fixed::max(cx, cy) << std::endl;

	std::cout << "\n=== Conversion Tests ===\n";
	Fixed z(10.75f);
	std::cout << "z: " << z << std::endl;
	std::cout << "z.toInt(): " << z.toInt() << std::endl;
	std::cout << "z.toFloat(): " << z.toFloat() << std::endl;

	// std::cout << "\n=== Edge Case: Division by Zero ===\n";
	// Fixed zero;
	// try {
	// 	std::cout << "z / zero = " << (z / zero) << std::endl;
	// } catch (...) {
	// 	std::cout << "Caught division by zero\n";
	// }

	std::cout << "\n=== Post-Decrement ===\n";
	Fixed d(3);
	std::cout << "d: " << d << std::endl;
	std::cout << "d--: " << d-- << std::endl;
	std::cout << "after d--: " << d << std::endl;
	std::cout << "--d: " << --d << std::endl;
	std::cout << "after --d: " << d << std::endl;

	return 0;
}
