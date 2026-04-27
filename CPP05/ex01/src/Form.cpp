#include <iostream>
#include <ostream>
#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form(const std::string& name, const int signGrade, const int executeGrade) : _name(name), _sign(false), _signGrade(signGrade), _executeGrade(executeGrade) {
	if (_signGrade < 1 || _executeGrade < 1)
		throw GradeTooHighException();
	else if (_signGrade > 150 || _executeGrade > 150)
		throw GradeTooLowException();
}

Form::Form(const Form& other) : _name(other._name), _sign(other._sign), _signGrade(other._signGrade), _executeGrade(other._executeGrade) {}

Form& Form::operator=(const Form& other) {
	if (this != &other) {
		this->_sign = other._sign;
	}
	return *this;
}

Form::~Form() {}

const std::string& Form::getName() const {
	return this->_name;
}

const bool& Form::getSign() const {
	return this->_sign;
}

const int& Form::getSignGrade() const {
	return this->_signGrade;
}

const int& Form::getExecuteGrade() const {
	return this->_executeGrade;
}

void Form::beSigned(const Bureaucrat& b) {
	if (b.getGrade() <= this->_signGrade) {
		this->_sign = true;
	}
	else {
		throw GradeTooLowException();
	}
}

void Form::beExecute(const Bureaucrat& b) {
	if (!this->_sign)
		throw FormNotSignedException();
	if (b.getGrade() <= this->_executeGrade) {
		this->_sign = true;
	}
	else {
		throw GradeTooLowException();
	}
}

const char* Form::GradeTooHighException::what() const throw() {
	return "Grade Too High for form";
}

const char* Form::GradeTooLowException::what() const throw() {
	return "Grade Too Low for form";
}

const char* Form::FormNotSignedException::what() const throw() {
	return "Form Not Signed";
}

std::ostream& operator<<(std::ostream& COUT, const Form& other) {
	return COUT << "Form name: " << other.getName()
				<< "\nForm signed: " << other.getSign()
				<< "\nForm sign grade: " << other.getSignGrade()
				<< "\nForm execute grade: " << other.getExecuteGrade();
}
