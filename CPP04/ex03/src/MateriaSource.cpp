#include <iostream>
#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "MateriaSource.hpp"

MateriaSource::MateriaSource() {
	for (int i = 0; i < this->_slotsSize; i++) {
		this->_slots[i] = NULL;
	}
}

MateriaSource::MateriaSource(const MateriaSource& other) {
	for (int i = 0; i < this->_slotsSize; i++) {
		if (other._slots[i])
			this->_slots[i] = other._slots[i]->clone();
		else
			this->_slots[i] = NULL;
	}
}

MateriaSource& MateriaSource::operator=(const MateriaSource& other) {
	if (this != &other) {
		for (int i = 0; i < this->_slotsSize; i++) {
			delete this->_slots[i];
			this->_slots[i] = NULL;
			if (other._slots[i])
				this->_slots[i] = other._slots[i]->clone();
		}
	}
	return *this;
}

MateriaSource::~MateriaSource() {
	for (int i = 0; i < this->_slotsSize; i++) {
		delete this->_slots[i];
	}
}

void MateriaSource::learnMateria(AMateria* m) {
	if (!m) {
		std::cout
			<< "Trying to learn unknown materia!\n";
		return;
	}
	for (int i = 0; i < this->_slotsSize; i++) {
		if (this->_slots[i] && (this->_slots[i]->getType() == m->getType())) {
			std::cout
				<< "Materia type[\"" << m->getType()
				<< "\"] already learned!\n";
			delete m;
			return;
		}
	}
	for (int i = 0; i < this->_slotsSize; i++) {
		if (!this->_slots[i]) {
			this->_slots[i] = m;
			std::cout
				<< "Materia type[\"" << m->getType()
				<< "\"] saved at materia source[" << i << "]\n";
			return;
		}
	}
}

AMateria* MateriaSource::createMateria(const std::string& type) {
	if (type == "ice" || type == "Ice")
		return new Ice();
	if (type == "cure" || type == "Cure")
		return new Cure();
	std::cout
		<< "Created unknown type of materia!\n";
	return NULL;
}
