#include <iostream>
#include "Harl.hpp"

Harl::Harl() {}

Harl::~Harl() {}

void Harl::debug() {
	std::cout
		<< "DEBUG: "
		<< "I love having extra bacon for my 7XL-double-cheese-triple-picke-special-ketchup burger. I really do!\n";
}

void Harl::info() {
	std::cout
		<< "INFO: "
		<< "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn't be asking for more!\n";
}
void Harl::warning() {
	std::cout
		<< "WARNING: "
		<< "I think I deserve to have some extra bacon for free. I've been coming for years whereas you started working here since last month.\n";
}
void Harl::error() {
	std::cout
		<< "ERROR: "
		<< "This is unacceptable! I want to speak to the manager now.\n";
}

void Harl::complain(std::string level) {
	std::string arr[] = {
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR"
	};

	void (Harl::*harlArr[])() = {
		&Harl::debug,
		&Harl::info,
		&Harl::warning,
		&Harl::error
	};

	int i = -1;
	while (++i < 4 && level != arr[i])
		;

	switch (i) {
		case 0:
			(this->*harlArr[0])();
		case 1:
			(this->*harlArr[1])();
		case 2:
			(this->*harlArr[2])();
		case 3:
			(this->*harlArr[3])();
			break;
		default:
			std::cout << "[ Probably complaining about insignificant problems ]\n";
	}
}
