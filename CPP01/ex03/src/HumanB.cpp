#include <iostream>
#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"

HumanB::HumanB(std::string name) : name(name), weapon(NULL) {}

HumanB::~HumanB() {}

void HumanB::attack() {
	if (!this->weapon)
		std::cout
			<< this->name << " has no weapon.\n";
	else
		std::cout
			<< this->name << " attacks with their '"
			<< this->weapon->getType() << "'\n";
}

void HumanB::setWeapon(Weapon& weapon) {
	this->weapon = &weapon;
}
