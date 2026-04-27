#include <iostream>
#include "Zombie.hpp"
#include "newZombie.hpp"
#include "randomChump.hpp"

int main() {
	Zombie *zom1 = newZombie("zom1");
	zom1->announce();
	randomChump("ranZ1");
	delete zom1;
	return 0;
}
