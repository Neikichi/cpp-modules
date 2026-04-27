#include <iostream>
#include <cmath>
#include "Fixed.hpp"

Fixed::Fixed() : rawVal(0) {
	std::cout
		<< "Default constructor called\n";
}

Fixed::Fixed(int n) : rawVal(n * (1 << fracBits)) {
	std::cout
		<< "Default constructor called\n";
}

Fixed::Fixed(float n) : rawVal(static_cast<int>(roundf(n * (1 << fracBits)))) {
	std::cout
		<< "Default constructor called\n";
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
	std::cout
		<< "getRawBits member function called\n";
	return this->rawVal;
}

void Fixed::setRawBits(int const raw) {
	this->rawVal = raw;
}
