#include <iostream>
#include <list>
#include <sstream>
#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& other) : _stack(other._stack), _token(other._token) {}

RPN& RPN::operator=(const RPN& other) {
	if (this != &other) {
		this->_stack = other._stack;
		this->_token = other._token;
	}
	return *this;
}

RPN::~RPN() {}

static std::size_t ssToStack(const std::string& s) {
	std::stringstream ss(s);
	std::size_t val;
	if (!(ss >> val))
		throw std::runtime_error("Error: ss to stack failed");
	return val;
}

static bool validToken(const std::string& s) {
	std::stringstream ss(s);
	char remains;
	std::string token;
	ss >> token;
	if (ss.fail() || ss >> remains)
		return false;

	const std::string op = "+-*/";
	if (token.length() == 1 && op.find(token[0]) != std::string::npos)
		return true;

	std::stringstream iss(token);
	std::size_t val;
	if (!(iss >> val) || iss >> remains)
		return false;

	return true;
}

void RPN::loadToken(const std::string& s) {
	std::stringstream ss(s);
	std::string token;
	while (ss >> token) {
		if (!validToken(token))
			throw std::runtime_error("Error: invalid input");
		_token.push_back(token);
	}
}

void RPN::calculate(const std::string& s) {
	const std::string op = OPERATORS;
	loadToken(s);
	
	std::list<std::string>::iterator it = _token.begin();
	for (; it != _token.end(); ++it) {
		if (it->length() == 1 && op.find((*it)[0]) != std::string::npos && _stack.size() >= 2) {
			std::size_t a, b;
			b = _stack.front();
			_stack.pop_front();
			a = _stack.front();
			_stack.pop_front();

			switch ((*it)[0]) {
				case '+':
					_stack.push_front(a + b);
					break;
				case '-':
					_stack.push_front(a - b);
					break;
				case '*':
					_stack.push_front(a * b);
					break;
				case '/':
					if (!b)
						throw std::runtime_error("Error: division by zero");
					_stack.push_front(a / b);
					break;
				default:
					throw std::runtime_error("Error: invalid operator");
			}
		}
		else
			_stack.push_front(ssToStack(*it));
	}
	if (_stack.size() != 1)
		throw std::runtime_error("Error: invalid RPN syntax");
	std::cout << "(" << s << ") = " << _stack.front() << "." << std::endl;
}
