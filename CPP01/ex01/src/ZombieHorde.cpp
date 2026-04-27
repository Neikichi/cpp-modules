#include <iostream>
#include "Zombie.hpp"

Zombie* zombieHorde(int n, std::string name) {

	if (n < 1)
		return NULL;
	
	Zombie *zomArr = new Zombie[n];
	Zombie zom1 = Zombie(name);
	for (int i = 0; i < n; i++) {
		zomArr[i] = zom1;
	}
	return zomArr;
}
