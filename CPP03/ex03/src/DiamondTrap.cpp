#include <iostream>
#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : ClapTrap("DiamondAI_clap_name"){
	std::cout
		<< "DiamondTrap Default constructor called\n";
	this->_name = "DiamondAI";
	this->setHP(100);
	this->setEP(50);
	this->setAD(30);
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name"), ScavTrap(), FragTrap(), _name(name) {
	std::cout
		<< "DiamondTrap Default constructor called\n";
	this->setHP(100);
	this->setEP(50);
	this->setAD(30);
}

DiamondTrap::DiamondTrap(const DiamondTrap& other) : ClapTrap(other), ScavTrap(other), FragTrap(other), _name(other._name) {
	std::cout
		<< "DiamondTrap Copy constructor called\n";
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other) {
	std::cout
		<< "DiamondTrap Assignment operator called\n";
	if (this != &other) {
		ClapTrap::operator=(other);
		_name = other._name;
	}
	return *this;
}

DiamondTrap::~DiamondTrap() {
	std::cout
		<< "DiamondTrap Destructor called\n";
}

void DiamondTrap::whoAmI() {
	std::cout
		<< "I am " << _name
		<< " and my parent is " << getName()
		<< ".\n";
}

void DiamondTrap::attack(const std::string& target) {
	ScavTrap::attack(target);
}
