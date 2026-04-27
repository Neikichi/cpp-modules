#include <iostream>
#include "Dog.hpp"
#include "Brain.hpp"

Dog::Dog() : Animal("Dog"), brain(new Brain) {
	std::cout
		<< "Dog Default constructor called.\n";
}

Dog::Dog(const Dog& other) : Animal(other), brain(new Brain(*other.brain)) {
	std::cout
		<< "Dog copy constructor called.\n";
}

Dog& Dog::operator=(const Dog& other) {
	std::cout
		<< "Dog assignment operator called.\n";
	if (this != &other) {
		this->_type = other._type;
		if (this->brain && other.brain)
			*this->brain = *other.brain;
	}
	return *this;
}

Dog::~Dog() {
	std::cout
		<< "Dog Destructor called.\n";
	delete brain;
}

void Dog::makeSound() const {
	std::cout
		<< "Woof Wuf.\n";
}
