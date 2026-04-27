#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <list>

#define WHITESPACES " \t\n\r\v\f"
#define OPERATORS "+-*/"

class RPN {
private:
	std::list<std::size_t> _stack;
	std::list<std::string> _token;
	void loadToken(const std::string& s);
public:
	RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();

	void calculate(const std::string& s);
};

#endif
