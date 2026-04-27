#include <iostream>
#include "Intern.hpp"
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

Intern::Intern() {}

Intern::Intern(const Intern& other) {
	(void)other;
}

Intern& Intern::operator=(const Intern& other) {
	(void)other;
	return *this;
}

Intern::~Intern() {}

AForm* Intern::makeForm(const std::string& name, const std::string& target) {
	const std::string arr[3] = {
		"ShrubberyCreationForm",
		"RobotomyRequestForm",
		"PresidentialPardonForm"
	};
	int idx = -1;

	for (int i = 0; i < 3; i++) {
		if (name == "Form")
			break;
		if (name == arr[i] || arr[i].find(name) != std::string::npos) {
			idx = i;
			break ;
		}
	}
	
	switch (idx) {
	case 0:
		std::cout << "Intern create " << arr[idx] << ".\n";
		return new ShrubberyCreationForm(target);
	case 1:
		std::cout << "Intern create " << arr[idx] << ".\n";
		return new RobotomyRequestForm(target);
	case 2:
		std::cout << "Intern create " << arr[idx] << ".\n";
		return new PresidentialPardonForm(target);
	default:
		std::cout << "Intern: No Matching Form\n";
		return NULL;
	}
}
