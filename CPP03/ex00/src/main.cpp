#include <iostream>
#include "ClapTrap.hpp"

int main() {
	ClapTrap p1("p1");
	ClapTrap p2("p2");

	p1.beRepaired(10);
	for (int i = 0; i < 11; i++)
		p1.attack("p2");
	p2.takeDamage(10);
	p2.beRepaired(10);
	p1.beRepaired(10);
	p1.status();
	p2.status();

	return 0;
}
