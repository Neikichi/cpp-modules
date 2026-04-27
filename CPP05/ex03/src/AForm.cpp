#include <iostream>
#include <ostream>
#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(const std::string& name, const std::string& target, const int signGrade, const int executeGrade) : _name(name), _target(target), _sign(false), _signGrade(signGrade), _executeGrade(executeGrade) {
	if (_signGrade < 1 || _executeGrade < 1)
		throw GradeTooHighException();
	else if (_signGrade > 150 || _executeGrade > 150)
		throw GradeTooLowException();
}

AForm::AForm(const AForm& other) : _name(other._name), _target(other._target), _sign(other._sign), _signGrade(other._signGrade), _executeGrade(other._executeGrade) {}

AForm& AForm::operator=(const AForm& other) {
	if (this != &other) {
		this->_sign = other._sign;
	}
	return *this;
}

AForm::~AForm() {}

const std::string& AForm::getName() const {
	return this->_name;
}

const std::string& AForm::getTarget() const {
	return this->_target;
}

const bool& AForm::getSign() const {
	return this->_sign;
}

const int& AForm::getSignGrade() const {
	return this->_signGrade;
}

const int& AForm::getExecuteGrade() const {
	return this->_executeGrade;
}

void AForm::beSigned(const Bureaucrat& b) {
	if (b.getGrade() <= this->_signGrade) {
		this->_sign = true;
	}
	else {
		throw GradeTooLowException();
	}
}

const char* AForm::GradeTooHighException::what() const throw() {
	return "Grade Too High for form";
}

const char* AForm::GradeTooLowException::what() const throw() {
	return "Grade Too Low for form";
}

const char* AForm::FormNotSignedException::what() const throw() {
	return "AForm Not Signed";
}

std::ostream& operator<<(std::ostream& COUT, const AForm& other) {
	return COUT << "AForm name: " << other.getName()
				<< "\nAForm signed: " << other.getSign()
				<< "\nAForm sign grade: " << other.getSignGrade()
				<< "\nAForm execute grade: " << other.getExecuteGrade();
}
