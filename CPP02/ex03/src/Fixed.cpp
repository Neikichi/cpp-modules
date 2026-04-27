#include <iostream>
#include <cmath>
#include "Fixed.hpp"

Fixed::Fixed() : rawVal(0) {
	// std::cout
	// 	<< "Default constructor called\n";
}

Fixed::Fixed(int n) : rawVal(n * (1 << fracBits)) {
	// std::cout
	// 	<< "Int constructor called\n";
}

Fixed::Fixed(float n) : rawVal(static_cast<int>(roundf(n * (1 << fracBits)))) {
	// std::cout
	// 	<< "Float constructor called\n";
}

Fixed::~Fixed() {
	// std::cout
	// 	<< "Destructor called\n";
}

Fixed::Fixed(const Fixed& other) {
	// std::cout
	// 	<< "Copy constructor called\n";
	*this = other;
}

Fixed& Fixed::operator=(const Fixed& other) {
	// std::cout
	// 	<< "Copy assignment constructor called\n";
	if (this != &other)
		this->rawVal = other.getRawBits();
	return *this;
}

bool Fixed::operator==(const Fixed& other) const{
	return this->rawVal == other.rawVal;
}

bool Fixed::operator!=(const Fixed& other) const{
	return this->rawVal != other.rawVal;
}

bool Fixed::operator>=(const Fixed& other) const{
	return this->rawVal >= other.rawVal;
}

bool Fixed::operator<=(const Fixed& other) const{
	return this->rawVal <= other.rawVal;
}

bool Fixed::operator>(const Fixed& other) const{
	return this->rawVal > other.rawVal;
}

bool Fixed::operator<(const Fixed& other) const{
	return this->rawVal < other.rawVal;
}

Fixed Fixed::operator+(const Fixed& other) const{
	Fixed ret;
	ret.rawVal = this->rawVal + other.rawVal;
	return ret;
}

Fixed Fixed::operator-(const Fixed& other) const{
	Fixed ret;
	ret.rawVal = this->rawVal - other.rawVal;
	return ret;
}

Fixed Fixed::operator*(const Fixed& other) const{
	Fixed ret;
	ret.rawVal = (this->rawVal * other.rawVal) >> fracBits;
	return ret;
}

Fixed Fixed::operator/(const Fixed& other) const{
	Fixed ret;
	ret.rawVal = (this->rawVal << fracBits) / other.rawVal;
	return ret;
}

Fixed& Fixed::operator++() {
	++rawVal;
	return *this;
}

Fixed Fixed::operator++(int) {
	Fixed temp = *this;
	rawVal++;
	return temp;
}

Fixed& Fixed::operator--() {
	--rawVal;
	return *this;
}

Fixed Fixed::operator--(int) {
	Fixed temp = *this;
	rawVal--;
	return temp;
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

Fixed& Fixed::min(Fixed& other1, Fixed& other2) {
	if (other1.rawVal > other2.rawVal)
		return other2;
	return other1;
}

const Fixed& Fixed::min(const Fixed& other1, const Fixed& other2) {
	if (other1.getRawBits() > other2.getRawBits())
		return other2;
	return other1;
}

Fixed& Fixed::max(Fixed& other1, Fixed& other2) {
	if (other1.rawVal < other2.rawVal)
		return other2;
	return other1;
}

const Fixed& Fixed::max(const Fixed& other1, const Fixed& other2) {
	if (other1.getRawBits() < other2.getRawBits())
		return other2;
	return other1;
}

std::ostream& operator<<(std::ostream& COUT, const Fixed& other) {
	return COUT << other.toFloat();
}
