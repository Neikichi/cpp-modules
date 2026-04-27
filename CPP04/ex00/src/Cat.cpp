#include <iostream>
#include "Cat.hpp"

Cat::Cat() : Animal("Cat") {
	std::cout
		<< "Cat Default constructor called.\n";
}

Cat::Cat(const Cat& other) {
	std::cout
		<< "Cat copy constructor called.\n";
	this->_type = other._type;
}

Cat& Cat::operator=(const Cat& other) {
	std::cout
		<< "Cat assignment operator called.\n";
	if (this != &other) {
		this->_type = other._type;
	}
	return *this;
}

Cat::~Cat() {
	std::cout
		<< "Cat Destructor called.\n";
}

void Cat::makeSound() const {
	std::cout
		<< "Meoww-nyan.\n";
}
