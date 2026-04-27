#include <iostream>
#include <ostream>
#include "Bureaucrat.hpp"

void	promotion(Bureaucrat& b) {
	try {
		std::cout
			<< b.getName() << ": of Grade: "
			<< b.getGrade() << " , trying to promote...\n";
		b.promote();
	}
	catch (const Bureaucrat::GradeTooHighException& e) {
		std::cerr
			<< "Error: " << e.what() << std::endl;
		return;
	}
	std::cout
		<< "Success: " << b << std::endl;
}

void	demotion(Bureaucrat& b) {
	try {
		std::cout
			<< b.getName() << ": of Grade: "
			<< b.getGrade() << " , trying to demote...\n";
		b.demote();
	}
	catch (const Bureaucrat::GradeTooLowException& e) {
		std::cerr
			<< "Error: " << e.what() << std::endl;
		return;
	}
	std::cout
		<< "Success: " << b << std::endl;
}

int main()
{
	Bureaucrat Warlock = Bureaucrat("Warlock", 1);
	Bureaucrat HighWizard = Bureaucrat("High Wizard", 25);
	Bureaucrat Wizard = Bureaucrat("Wizard", 50);
	Bureaucrat Mage = Bureaucrat("Mage", 100);
	Bureaucrat Novice = Bureaucrat("Novice", 150);

	promotion(Warlock);
	demotion(Novice);
	promotion(HighWizard);
	demotion(Mage);
	promotion(Wizard);
	demotion(Wizard);
}
