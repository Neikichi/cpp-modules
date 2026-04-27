#include <iostream>
#include "Zombie.hpp"
#include "newZombie.hpp"
#include "randomChump.hpp"

void randomChump(std::string name) {
	Zombie *chump1 = newZombie(name);
	chump1->announce();
	delete chump1;
}
