#include <iostream>
#include "FragTrap.hpp"

int main() {
	std::cout << "=== Create original FragTrap ===\n";
	FragTrap original;
	original.highFiveGuys();
	original.attack("Edwin");

	std::cout << "\n=== Copy constructor ===\n";
	FragTrap copy(original);
	copy.highFiveGuys();

	std::cout << "\n=== Assignment operator ===\n";
	FragTrap assigned;
	assigned = original;
	assigned.highFiveGuys();

	std::cout << "\n=== Modify original and check copy ===\n";
	original.setName("ModifiedBot");
	original.setHP(42);
	original.setEP(1);
	original.setAD(999);
	original.highFiveGuys();
	original.attack("Edwin");
	original.status();

	std::cout << "\nCopy's state remains unchanged:\n";
	copy.highFiveGuys();

	// std::cout << "=== Direct destruction ===\n";
	// {
	// 	FragTrap direct("direct");
	// }
	//
	// std::cout << "\n=== Base pointer deletion ===\n";
	// {
	// 	ClapTrap* polyFrag = new FragTrap("polyFrag");
	// 	delete polyFrag;
	// }

	return 0;
}

