#include <iostream>
#include "Character.hpp"
#include "AMateria.hpp"

Character::Character(const std::string& name) : _name(name), _trashCan(NULL), _trashCanSize(0) {
	for (int i = 0; i < _slotsSize; i++) {
			this->_slots[i] = NULL;
	}
}

Character::Character(const Character& other) : _name(other._name), _trashCan(NULL), _trashCanSize(0) {
	for (int i = 0; i < _slotsSize; i++) {
		if (other._slots[i])
			this->_slots[i] = other._slots[i]->clone();
		else
			this->_slots[i] = NULL;
	}
}

Character& Character::operator=(const Character& other) {
	if (this != &other) {
		// this->_name = other._name;
		for (int i = 0; i < _slotsSize; i++) {
			delete this->_slots[i];
			if (other._slots[i])
				this->_slots[i] = other._slots[i]->clone();
			else
				this->_slots[i] = NULL;
		}
		for (int i = 0; i < _trashCanSize; i++) {
			delete this->_trashCan[i];
		}
		delete[] this->_trashCan;
		this->_trashCan = NULL;
		this->_trashCanSize = 0;
	}
	return *this;
}

Character::~Character() {
	for (int i = 0; i < _slotsSize; i++) {
		delete this->_slots[i];
	}
	for (int i = 0; i < _trashCanSize; i++) {
		delete this->_trashCan[i];
	}
	delete[] this->_trashCan;
}

const std::string& Character::getName() const {
	return this->_name;
}

void Character::equip(AMateria* m) {
	if (!m) {
		std::cout
			<< this->_name << ": Trying to equip an unknown type of materia!\n";
		return;
	}
	for (int i = 0; i < this->_slotsSize; i++) {
		if (!this->_slots[i]) {
			this->_slots[i] = m;
			std::cout
				<< this->_name << ": equiped "
				<< m->getType() <<" at inventory slot["
				<< i << "]\n";
			return;
		}
	}
	this->discard(m);
	std::cout
		<< this->_name << ": Inventory is full!\n";
}

void Character::unequip(int idx) {
	if (idx >= 0 && idx < this->_slotsSize) {
		if (this->_slots[idx])
		{
			this->discard(this->_slots[idx]);
			this->_slots[idx] = NULL;
			std::cout << "Inventory slots[" << idx << "] has been unequip\n";
			return;
		}
		std::cout
			<< this->_name
			<< ": Trying to unequip empty inventory slots!\n";
		return;
	}
	std::cout
		<< this->_name
		<< ": Trying to unequip invalid inventory slots!\n";
}

void Character::use(int idx, ICharacter& target) {
	if (idx >= 0 && idx < this->_slotsSize) {
		if (this->_slots[idx]) {
			this->_slots[idx]->use(target);
			delete this->_slots[idx];
			this->_slots[idx] = NULL;
		}
		else {
			std::cout
				<< this->_name << ": Trying to use empty inventory slot!\n";
		}
	}
	else
		std::cout
			<< this->_name
			<< ": Trying to use invalid inventory slots!\n";
}

void Character::discard(AMateria* m) {
	AMateria** tempCan = new AMateria*[this->_trashCanSize + 1];
	for (int i = 0; i < _trashCanSize; i++) {
		tempCan[i] = _trashCan[i];
	}
	tempCan[_trashCanSize] = m;
	delete[] _trashCan;
	this->_trashCan = tempCan;
	this->_trashCanSize++;
}
