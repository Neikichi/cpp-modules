#include "DiamondTrap.hpp"
#include <iostream>

int main() {
	{
		std::cout << "=== Default Constructor ===\n";
		DiamondTrap defaultBot;
		defaultBot.whoAmI();
		defaultBot.attack("DefaultTarget");
		defaultBot.guardGate();
		defaultBot.highFiveGuys();
		defaultBot.attack("Edwin");
		defaultBot.status();

		std::cout << "\n=== Named Constructor ===\n";
		DiamondTrap namedBot("VeeBot");
		namedBot.whoAmI();
		namedBot.attack("NamedTarget");
		namedBot.guardGate();
		namedBot.highFiveGuys();
		namedBot.attack("Edwin");
		namedBot.status();

		std::cout << "\n=== Copy Constructor ===\n";
		DiamondTrap copiedBot(namedBot);
		copiedBot.whoAmI();
		copiedBot.guardGate();
		copiedBot.highFiveGuys();
		copiedBot.attack("Edwin");
		copiedBot.status();

		std::cout << "\n=== Assignment Operator ===\n";
		DiamondTrap assignedBot;
		assignedBot = copiedBot;
		assignedBot.whoAmI();
		assignedBot.guardGate();
		assignedBot.highFiveGuys();
		assignedBot.attack("Edwin");
		assignedBot.status();

		std::cout << "\n=== Destructor calls (end of main) ===\n";
	}



	// {
	// 	std::cout << "=== Polymorphism: ClapTrap pointer to ScavTrap ===\n";
	// 	ClapTrap* ct1 = new ScavTrap("PolyScav");
	// 	ct1->attack("Target1");
	// 	delete ct1;
	//
	// 	std::cout << "\n=== Polymorphism: ClapTrap pointer to FragTrap ===\n";
	// 	ClapTrap* ct2 = new FragTrap("PolyFrag");
	// 	ct2->attack("Target2");
	// 	delete ct2;
	//
	// 	std::cout << "\n=== Polymorphism: ClapTrap pointer to DiamondTrap ===\n";
	// 	ClapTrap* ct3 = new DiamondTrap("PolyDiamond");
	// 	ct3->attack("Target3");
	// 	delete ct3;
	//
	// 	std::cout << "\n=== Polymorphism: No virtual destructor ===\n";
	// 	std::cout << "(Comment out virtual ~ClapTrap() to test destructor skipping)\n";
	// }

	return 0;
}
