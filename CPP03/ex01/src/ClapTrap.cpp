#include <iostream>
#include <string>
#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : _name("ClapAI"), _hitPoints(10), _energyPoints(10), _atkDmg(0) {
	std::cout
		<< "ClapTrap Default constructor called\n";
}

ClapTrap::ClapTrap(std::string name) : _name(name), _hitPoints(10), _energyPoints(10), _atkDmg(0) {
	std::cout
		<< "ClapTrap constructor called\n";
}

ClapTrap::ClapTrap(const ClapTrap& other) {
	std::cout
		<< "ClapTrap Copy constructor called\n";

	this->_name = other._name;
	this->_hitPoints = other._hitPoints;
	this->_energyPoints = other._energyPoints;
	this->_atkDmg = other._atkDmg;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other) {
	std::cout
		<< "ClapTrap Assignment constructor called\n";

	this->_name = other._name;
	this->_hitPoints = other._hitPoints;
	this->_energyPoints = other._energyPoints;
	this->_atkDmg = other._atkDmg;
	return *this;
}

ClapTrap::~ClapTrap() {
	std::cout
		<< "ClapTrap Destructor called\n";
}

void ClapTrap::attack(const std::string& target) {
	if (this->_energyPoints < 1) {
		std::cout
			<< "ClapTrap " << this->_name
			<< " tries to attack " << target
			<< ", but has no energy. weak!\n";
		return;
	}
	this->_energyPoints--;
	std::cout
		<< "ClapTrap " << this->_name
		<< " attacks " << target
		<< ", causing " << this->_atkDmg
		<< " points of damage!\n";
}

void ClapTrap::takeDamage(unsigned int amount) {
	if (this->_hitPoints < 1) {
		std::cout
			<< "ClapTrap " << this->_name
			<< " has no hit points left. Dead!\n";
		return;
	}
	if (this->_hitPoints == 1) {
		std::cout
			<< "ClapTrap " << this->_name
			<< " has taken " << amount
			<< " points of damage and has no hit points left. Died!\n";
		this->_hitPoints -= amount;
		return;
	}
	this->_hitPoints -= amount;
	std::cout
		<< "ClapTrap " << this->_name
		<< " has taken " << amount
		<< " points of damage! Ouch!\n";
}

void ClapTrap::beRepaired(unsigned int amount) {
	if (this->_energyPoints < 1) {
		std::cout
			<< "ClapTrap " << this->_name
			<< " tries to recover hit points, but has no energy. weak!\n";
		return;
	}
	this->_energyPoints--;
	this->_hitPoints += amount;
	std::cout
		<< "ClapTrap " << this->_name
		<< " has used 1 energy point to heal " << amount
		<< " of hit points!\n";
}

void ClapTrap::setName(const std::string name) {
	this->_name = name;
}

void ClapTrap::setHP(unsigned int amount) {
	this->_hitPoints = amount;
}

void ClapTrap::setEP(unsigned int amount) {
	this->_energyPoints = amount;
}

void ClapTrap::setAD(unsigned int amount) {
	this->_atkDmg = amount;
}

std::string ClapTrap::getName() const {
	return this->_name;
}

int ClapTrap::getHP() const {
	return this->_hitPoints;
}

int ClapTrap::getEP() const {
	return this->_energyPoints;
}

int ClapTrap::getAD() const {
	return this->_atkDmg;
}

void ClapTrap::status() const {
	std::cout
		<< this->_name << " Status Window!\n"
		<< "HP: " << this->_hitPoints << "\n"
		<< "EP: " << this->_energyPoints << "\n"
		<< "AD: " << this->_atkDmg << "\n";
}
