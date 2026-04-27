#include <iostream>
#include "ShrubberyCreationForm.hpp"
#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target) : AForm("ShrubberyCreationForm", target, 145, 137) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other) : AForm(other) {}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other) {
	if (this != &other) {
		AForm::operator=(other);
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

void ShrubberyCreationForm::execute(const Bureaucrat& executor) const {
	if (!this->getSign())
		throw FormNotSignedException();
	if (executor.getGrade() > this->getExecuteGrade()) {
		throw GradeTooLowException();
	}
	std::ofstream file((this->getTarget() + "_shrubbery").c_str());
	if (!file)
		throw std::ios_base::failure("Failed to open the output file");

	file << "       oxoxoo    ooxoo\n";
	file << "     ooxoxo oo  oxoxooo\n";
	file << "    oooo xxoxoo ooo ooox\n";
	file << "    oxo o oxoxo  xoxxoxo\n";
	file << "     oxo xooxoooo o ooo\n";
	file << "       ooo\\\\oo\\\\  /o/o\n";
	file << "           \\\\  \\\\/ /\n";
	file << "            |   /\n";
	file << "            |  |\n";
	file << "            | D|\n";
	file << "            |  |\n";
	file << "            |  |\n";
	file << "     ______/____\\\\____\n";
	file.close();
}
