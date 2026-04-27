#ifndef AFORM_HPP
#define AFORM_HPP

#include <exception>
#include <iostream>
#include <ostream>

class Bureaucrat;

class AForm {
private:
	const std::string _name;
	const std::string _target;
	bool _sign;
	const int _signGrade;
	const int _executeGrade;
public:
	AForm(const std::string& name, const std::string& target, const int signGrade, const int executeGrade);
	AForm(const AForm& other);
	AForm& operator=(const AForm& other);
	virtual ~AForm();

	const std::string& getName() const;
	const std::string& getTarget() const;
	const bool& getSign() const;
	const int& getSignGrade() const;
	const int& getExecuteGrade() const;
	void beSigned(const Bureaucrat& b);
	virtual void execute(const Bureaucrat& executor) const = 0;
	

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

std::ostream& operator<<(std::ostream& COUT, const AForm& other);

#endif
