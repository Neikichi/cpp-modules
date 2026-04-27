#include <iostream>
#include "ClapTrap.hpp"
#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap("FragAI"){
	std::cout
		<< "FragTrap Default constructor called\n";
	this->setHP(100);
	this->setEP(100);
	this->setAD(30);
}

FragTrap::FragTrap(std::string name) : ClapTrap(name) {
	std::cout
		<< "FragTrap Default Named constructor called\n";
	this->setHP(100);
	this->setEP(100);
	this->setAD(30);
}

FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other) {
	std::cout
		<< "FragTrap Copy constructor called\n";
}

FragTrap& FragTrap::operator=(const FragTrap& other) {
	std::cout
		<< "FragTrap Assignment operator called\n";
	if (this != &other) {
		ClapTrap::operator=(other);
	}
	return *this;
}

FragTrap::~FragTrap() {
	std::cout
		<< "FragTrap Destructor called\n";
}

void FragTrap::highFiveGuys() {
	std::cout
		<< "FragTrap " << this->getName()
		<< " is gonna high five!\n";
}

void FragTrap::attack(const std::string& target) {
	if (this->_energyPoints < 1) {
		std::cout
			<< "FragTrap " << this->_name
			<< " tries to attack " << target
			<< ", but has no energy. weak!\n";
		return;
	}
	this->_energyPoints--;
	std::cout
		<< "FragTrap " << this->_name
		<< " attacks " << target
		<< ", causing " << this->_atkDmg
		<< " points of damage!\n";
}
