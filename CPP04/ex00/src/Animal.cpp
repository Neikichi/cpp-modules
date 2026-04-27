#include <iostream>
#include <string>
#include "Animal.hpp"

Animal::Animal() : _type("Spirit") {
	std::cout
		<< "Animal Default constructor called.\n";
}

Animal::Animal(std::string type) : _type(type) {
	std::cout
		<< "Animal Default constructor called.\n";
}

Animal::Animal(const Animal& other) {
	std::cout
		<< "Animal copy constructor called.\n";
	this->_type = other._type;
}

Animal& Animal::operator=(const Animal& other) {
	std::cout
		<< "Animal assignment operator called.\n";
	if (this != &other) {
		this->_type = other._type;
	} return *this;
}

Animal::~Animal() {
	std::cout
		<< "Animal Destructor called.\n";
}

void Animal::makeSound() const {
	std::cout
		<< "Animal still a spirit.\n";
}

std::string Animal::getType() const{
	return this->_type;
}
