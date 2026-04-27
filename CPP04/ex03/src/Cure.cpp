#include <iostream>
#include "Cure.hpp"
#include "AMateria.hpp"
#include "ICharacter.hpp"

Cure::Cure() : AMateria("Cure") {}

Cure::Cure(const Cure& other) : AMateria(other) {}

Cure& Cure::operator=(const Cure& other) {
	(void)other;
	return *this;
}

Cure::~Cure() {}

AMateria* Cure::clone() const {
	return new Cure();
}

void Cure::use(ICharacter& target) {
	std::cout
		<< "Cure: '* heals " << target.getName()
		<< "'s wounds *'\n";
}

