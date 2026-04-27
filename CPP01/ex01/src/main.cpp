#include <iostream>
#include "Zombie.hpp"
#include "ZombieHorde.hpp"

int main() {
	int size = 8;
	Zombie *zomArr = zombieHorde(size, "Zombieee");
	for (int i = 0; i < size; i++)
	{
		std::cout << i + 1 << ". ";
		zomArr[i].announce();
	}
	delete[] zomArr;

	return 0;
}
