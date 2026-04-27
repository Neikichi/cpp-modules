#include <cstdlib>
#include <ctime>
#include <iostream>
#include "RobotomyRequestForm.hpp"
#include "AForm.hpp"
#include "Bureaucrat.hpp"

RobotomyRequestForm::RobotomyRequestForm(const std::string& target) : AForm("RobotomyRequestForm", target, 72, 45) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other) : AForm(other) {}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other) {
	if (this != &other)
		AForm::operator=(other);
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {}

void RobotomyRequestForm::execute(const Bureaucrat& executor) const {
	if (!this->getSign())
		throw FormNotSignedException();
	if (executor.getGrade() > this->getExecuteGrade()) {
		throw GradeTooLowException();
	}
	srand(time(0));
	if (rand() % 100 < 50) {
		std::cout
			<< "DrRzzZzz DrRzzZzz "
			<< this->getTarget() << " has been successfully robotomized.\n";
	}
	else {
		std::cout
			<< this->getTarget() << " robotomization failed.\n";
	}
}
