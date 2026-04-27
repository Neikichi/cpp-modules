#include <iostream>
#include <ostream>
#include <exception>
#include "Bureaucrat.hpp"
#include "Form.hpp"

Bureaucrat::Bureaucrat(const std::string& name, int grade) : _name(name) {
	if (grade < 1)
		throw GradeTooHighException();
	else if (grade > 150)
		throw GradeTooLowException();
	this->_grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat& other) : _name(other._name), _grade(other._grade) {}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
	if (this != &other)
	{
		// this->_name = other._name;
		this->_grade = other._grade;
	}
	return *this;
}

Bureaucrat::~Bureaucrat() {}

const std::string& Bureaucrat::getName() const {
	return this->_name;
}

const int& Bureaucrat::getGrade() const {
	return this->_grade;
}

void Bureaucrat::promote() {
	if (this->_grade - 1 < 1)
		throw GradeTooHighException();
	this->_grade--;
}

void Bureaucrat::demote() {
	if (this->_grade + 1 > 150)
		throw GradeTooLowException();
	this->_grade++;
}

void Bureaucrat::signForm(Form& f) {
	try {
		f.beSigned(*this);
	}
	catch (const Form::GradeTooLowException& e) {
		std::cerr
			<< this->getName() << " couldn't sign "
			<< f.getName() << " because "
			<< e.what() << ".\n";
		return;
	}
	std::cout
		<< this->getName() << " signed "
		<< f.getName() << std::endl;
}

void Bureaucrat::executeForm(Form& f) {
	try {
		f.beExecute(*this);
	}
	catch (const std::exception& e) {
		std::cerr
			<< this->getName() << " couldn't execute "
			<< f.getName() << " because "
			<< e.what() << ".\n";
		return;
	}
	std::cout
		<< this->getName() << " executed "
		<< f.getName() << std::endl;
}

const char* Bureaucrat::GradeTooHighException::what() const throw() {
	return "Grade Too High";
}

const char * Bureaucrat::GradeTooLowException::what() const throw() {
	return "Grade Too Low";
}

std::ostream& operator<<(std::ostream& COUT, const Bureaucrat& other) {
	return COUT << other.getName() << ", bureaucrat grade "
				<< other.getGrade() << ".";
}
