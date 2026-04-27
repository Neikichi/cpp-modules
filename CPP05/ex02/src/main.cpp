#include <cstdio>
#include <exception>
#include <iostream>
#include <ostream>
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <list>
#include <vector>

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

void	trySign(AForm& f, Bureaucrat& b) {
	std::cout
		<< b.getName() << ": attempts to sign form: "
		<< f.getName() << "...\n";
	b.signForm(f);
}

void tryExecute(AForm& f, Bureaucrat& b) {
	std::cout
		<< b.getName() << ": attempts to execute form: "
		<< f.getName() << "...\n";
	b.executeForm(f);
}

template <typename T>
void printContainers(const T& c)
{
	for (typename T::const_iterator it = c.begin(); it != c.end(); it++) {
		std::cout
			<< **it << std::endl;
	}
}

void printBureaucrats(const std::list<Bureaucrat*>& b) {
	std::list<Bureaucrat*>::const_iterator it;

	for (it = b.begin(); it != b.end(); it++) {
		std::cout << **it << std::endl;
	}
}

void printForms(const std::vector<AForm*>& f) {
	std::vector<AForm*>::const_iterator it;

	for (it = f.begin(); it != f.end(); it++) {
		std::cout << **it << std::endl;
	}
}

int main()
{
	Bureaucrat Warlock = Bureaucrat("Warlock", 1);
	Bureaucrat HighWizard = Bureaucrat("High Wizard", 25);
	Bureaucrat Wizard = Bureaucrat("Wizard", 50);
	Bureaucrat Mage = Bureaucrat("Mage", 100);
	Bureaucrat Novice = Bureaucrat("Novice", 150);

	// AForm FireBolt = AForm("FireBolt", 100, 100);
	// AForm MeteorStorm = AForm("MeteorStorm", 50, 50);
	// AForm AmplifyMP = AForm("AmplifyMP", 25, 25);
	// AForm Comet = AForm("Comet", 1, 1);

	ShrubberyCreationForm Shrubs = ShrubberyCreationForm("Mage");
	RobotomyRequestForm Robo = RobotomyRequestForm("Novice");
	PresidentialPardonForm Pres = PresidentialPardonForm("HighWizard");
	

	// List practice
	std::list<Bureaucrat*> Bureaucrats;

	Bureaucrats.push_back(&Warlock);
	Bureaucrats.push_back(&HighWizard);
	Bureaucrats.push_back(&Wizard);
	Bureaucrats.push_back(&Mage);
	Bureaucrats.push_back(&Novice);

	// Vector practice
	// std::vector<AForm*> Forms;

	// Forms.push_back(&FireBolt);
	// Forms.push_back(&MeteorStorm);
	// Forms.push_back(&AmplifyMP);
	// Forms.push_back(&Comet);

	std::cout << "\n===Print Bureaucrat===\n";
	printContainers(Bureaucrats);
	// std::cout << "\n===Print Forms===\n";
	// printContainers(Forms);

	std::cout << "\n===Bureaucrat===\n";
	promotion(Warlock);
	demotion(Novice);
	promotion(HighWizard);
	demotion(Mage);
	promotion(Wizard);
	demotion(Wizard);

	std::cout << "\n===Print Bureaucrat===\n";
	printBureaucrats(Bureaucrats);

	std::cout << "\n===Signing forms===\n";
	trySign(Shrubs, Mage);
	trySign(Robo, HighWizard);
	trySign(Pres, Wizard);
	trySign(Pres, Warlock);

	std::cout << "\n===Print Forms===\n";
	// printForms(Forms);
	std::cout << Shrubs << std::endl;
	std::cout << Robo << std::endl;
	std::cout << Pres << std::endl;

	std::cout << "\n===Execute forms===\n";
	tryExecute(Shrubs, Novice);
	tryExecute(Robo, Wizard);
	tryExecute(Shrubs, HighWizard);
	tryExecute(Pres, Mage);
	tryExecute(Pres, Warlock);
}
