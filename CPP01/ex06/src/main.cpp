#include <iostream>
#include "Harl.hpp"

int main(int ac, char *av[])
{
	if (ac != 2) {
		std::cout
			<< "Invalid arguments! Usage: ./harlFilter <DEBUG || INFO || WARNING || ERROR>\n";
		return 1;
	}

	Harl harl;
	harl.complain(av[1]);

	return 0;
}
