#include <iostream>
#include "WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal("WrongCat") {
	std::cout
		<< "WrongCat Default constructor called.\n";
}

WrongCat::WrongCat(const WrongCat& other) {
	std::cout
		<< "WrongCat copy constructor called.\n";
	this->_type = other._type;
}

WrongCat& WrongCat::operator=(const WrongCat& other) {
	std::cout
		<< "WrongCat assignment operator called.\n";
	if (this != &other) {
		this->_type = other._type;
	}
	return *this;
}

WrongCat::~WrongCat() {
	std::cout
		<< "WrongCat Destructor called.\n";
}

void WrongCat::makeSound() const {
	std::cout
		<< "Wrong Meoww-nyan.\n";
}
