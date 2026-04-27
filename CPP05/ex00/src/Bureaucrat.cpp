#include <iostream>
#include <Bureaucrat.hpp>
#include <ostream>

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
