#include <iostream>
#include "Zombie.hpp"

Zombie::Zombie() {}

Zombie::Zombie(std::string name) : name(name){}

Zombie::~Zombie() {
	std::cout
		<< this->name << ": is destroyed!\n";
}

void Zombie::announce() {
	std::cout
		<< this->name << ": BraiiiiiiinnnzzzZ...\n";
}

Zombie& Zombie::operator=(const Zombie& other) {
	if (this != &other) {
		this->name = other.name;
	}
	return *this;
}
