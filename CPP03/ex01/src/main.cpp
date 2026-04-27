#include <iostream>
#include "ScavTrap.hpp"

int main() {
	std::cout << "=== Create original ScavTrap ===\n";
	ScavTrap original;
	original.guardGate();
	original.attack("Edwin");

	std::cout << "\n=== Copy constructor ===\n";
	ScavTrap copy(original);
	copy.guardGate();

	std::cout << "\n=== Assignment operator ===\n";
	ScavTrap assigned;
	assigned = original;
	assigned.guardGate();

	std::cout << "\n=== Modify original and check copy ===\n";
	original.setName("ModifiedBot");
	original.setHP(42);
	original.setEP(1);
	original.setAD(999);
	original.attack("Edwin");
	original.guardGate();
	original.status();

	std::cout << "\nCopy's state remains unchanged:\n";
	copy.guardGate();

	// std::cout << "=== Direct destruction ===\n";
	// {
	// 	ScavTrap direct("direct");
	// }
	//
	// std::cout << "\n=== Base pointer deletion ===\n";
	// {
	// 	ClapTrap* polyScav = new ScavTrap("'polyScav");
	// 	delete polyScav;
	// }
	return 0;
}

