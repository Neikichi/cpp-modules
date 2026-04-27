#include <iostream>
#include <string>
#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : _type("Spirit") {
	std::cout
		<< "WrongAnimal Default constructor called.\n";
}

WrongAnimal::WrongAnimal(std::string type) : _type(type) {
	std::cout
		<< "WrongAnimal Default constructor called.\n";
}

WrongAnimal::WrongAnimal(const WrongAnimal& other) {
	std::cout
		<< "WrongAnimal copy constructor called.\n";
	this->_type = other._type;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other) {
	std::cout
		<< "WrongAnimal assignment operator called.\n";
	if (this != &other) {
		this->_type = other._type;
	} return *this;
}

WrongAnimal::~WrongAnimal() {
	std::cout
		<< "WrongAnimal Destructor called.\n";
}

void WrongAnimal::makeSound() const {
	std::cout
		<< "WrongAnimal still a spirit.\n";
}

std::string WrongAnimal::getType() const{
	return this->_type;
}
