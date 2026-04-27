#include <iostream>
#include "AMateria.hpp"
#include "ICharacter.hpp"

AMateria::AMateria() : _type("Empty") {}

AMateria::AMateria(const std::string& type) : _type(type) {}

AMateria::AMateria(const AMateria& other) : _type(other._type) {}

AMateria& AMateria::operator=(const AMateria& other) {
	(void)other;
	return *this;
}

AMateria::~AMateria() {}

const std::string& AMateria::getType() const {
	return this->_type;
}

void AMateria::use(ICharacter& target) {
	// (void)target;
	std::cout
		<< "Slots is empty: '* attempted to use nothing at "
		<< target.getName()
		<< " *'\n";
}
