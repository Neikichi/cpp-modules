#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap("ScavAI"){
	std::cout
		<< "ScavTrap Default constructor called\n";
	this->setHP(100);
	this->setEP(50);
	this->setAD(20);
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
	std::cout
		<< "ScavTrap Default Named constructor called\n";
	this->setHP(100);
	this->setEP(50);
	this->setAD(20);
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other) {
	std::cout
		<< "ScavTrap Copy constructor called\n";
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other) {
	std::cout
		<< "ScavTrap Assignment operator called\n";
	if (this != &other) {
		ClapTrap::operator=(other);
	}
	return *this;
}

ScavTrap::~ScavTrap() {
	std::cout
		<< "ScavTrap Destructor called\n";
}

void ScavTrap::guardGate() {
	std::cout
		<< "ScavTrap " << this->getName()
		<< " is now in Gate Keeper mode!\n";
}

void ScavTrap::attack(const std::string& target) {
	if (this->_energyPoints < 1) {
		std::cout
			<< "ScavTrap " << this->_name
			<< " tries to attack " << target
			<< ", but has no energy. weak!\n";
		return;
	}
	this->_energyPoints--;
	std::cout
		<< "ScavTrap " << this->_name
		<< " attacks " << target
		<< ", causing " << this->_atkDmg
		<< " points of damage!\n";
}
