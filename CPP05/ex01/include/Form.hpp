#ifndef FORM_HPP
#define FORM_HPP

#include <exception>
#include <iostream>
#include <ostream>

class Bureaucrat;

class Form {
private:
	const std::string _name;
	bool _sign;
	const int _signGrade;
	const int _executeGrade;
public:
	Form(const std::string& name, const int signGrade, const int executeGrade);
	Form(const Form& other);
	Form& operator=(const Form& other);
	~Form();

	const std::string& getName() const;
	const bool& getSign() const;
	const int& getSignGrade() const;
	const int& getExecuteGrade() const;
	void beSigned(const Bureaucrat& b);
	void beExecute(const Bureaucrat& b);

	class GradeTooHighException: public std::exception {
	public:
		const char* what() const throw();
	};

	class GradeTooLowException: public std::exception {
	public:
		const char* what() const throw();
	};

	class FormNotSignedException: public std::exception {
	public:
		const char* what() const throw();
	};
};

std::ostream& operator<<(std::ostream& COUT, const Form& other);

#endif
