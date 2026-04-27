#include <iostream>
#include "Cat.hpp"
#include "Brain.hpp"

Cat::Cat() : Animal("Cat"), brain(new Brain) {
	std::cout
		<< "Cat Default constructor called.\n";
}

Cat::Cat(const Cat& other) : Animal(other), brain(new Brain(*other.brain)) {
	std::cout
		<< "Cat copy constructor called.\n";
}

Cat& Cat::operator=(const Cat& other) {
	std::cout
		<< "Cat assignment operator called.\n";
	if (this != &other) {
		this->_type = other._type;
		if (this->brain && other.brain)
			*this->brain = *other.brain;
	}
	return *this;
}

Cat::~Cat() {
	std::cout
		<< "Cat Destructor called.\n";
	delete brain;
}

void Cat::makeSound() const {
	std::cout
		<< "Meoww-nyan.\n";
}
