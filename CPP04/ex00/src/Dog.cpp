#include <iostream>
#include "Dog.hpp"

Dog::Dog() : Animal("Dog") {
	std::cout
		<< "Dog Default constructor called.\n";
}

Dog::Dog(const Dog& other) {
	std::cout
		<< "Dog copy constructor called.\n";
	this->_type = other._type;
}

Dog& Dog::operator=(const Dog& other) {
	std::cout
		<< "Dog assignment operator called.\n";
	if (this != &other) {
		this->_type = other._type;
	}
	return *this;
}

Dog::~Dog() {
	std::cout
		<< "Dog Destructor called.\n";
}

void Dog::makeSound() const {
	std::cout
		<< "Woof Wuf.\n";
}
