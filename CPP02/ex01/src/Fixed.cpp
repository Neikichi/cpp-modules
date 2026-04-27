#include <iostream>
#include <cmath>
#include "Fixed.hpp"

Fixed::Fixed() : rawVal(0) {
	std::cout
		<< "Default constructor called\n";
}

Fixed::Fixed(int n) : rawVal(n * (1 << fracBits)) {
	std::cout
		<< "Int constructor called\n";
}

Fixed::Fixed(float n) : rawVal(static_cast<int>(roundf(n * (1 << fracBits)))) {
	std::cout
		<< "Float constructor called\n";
}

Fixed::~Fixed() {
	std::cout
		<< "Destructor called\n";
}

Fixed::Fixed(const Fixed& other) {
	std::cout
		<< "Copy constructor called\n";
	*this = other;
}

Fixed& Fixed::operator=(const Fixed& other) {
	std::cout
		<< "Copy assignment constructor called\n";
	if (this != &other)
		this->rawVal = other.getRawBits();
	return *this;
}

int Fixed::getRawBits() const {
	// std::cout
	// 	<< "getRawBits member function called\n";
	return this->rawVal;
}

float Fixed::toFloat() const {
	return static_cast<float>(this->rawVal) / (1 << this->fracBits);
}

int Fixed::toInt() const {
	return this->rawVal / (1 << this->fracBits);
}

std::ostream& operator<<(std::ostream& COUT, const Fixed& other) {
	return COUT << other.toFloat();
}

