#include <cctype>
#include <cstdlib>
#include <iostream>
#include "ScalarConverter.hpp"
#include <iomanip>
#include <limits>

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other) {
	(void)other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {
	(void)other;
	return *this;
}

ScalarConverter::~ScalarConverter() {}

void ScalarConverter::convertChar(const std::string& input) {
	std::cout << "===Convert Char===\n";
	std::cout << std::fixed << std::setprecision(2);

	if (std::isprint(input[0]))
		std::cout << "char: '" << input[0] << "'\n";
	else
		std::cout << "char: non displayable\n";

	std::cout << "int: " << static_cast<int>(input[0]) << "\n";
	std::cout << "float: " << static_cast<float>(input[0]) << "f\n";
	std::cout << "double: " << static_cast<double>(input[0]) << "\n";
}

void ScalarConverter::convertFloat(const std::string& input) {
	std::cout << "===Convert Float===\n";
	std::cout << std::fixed << std::setprecision(2);

	char *end;
	float f = std::strtof(input.c_str(), &end);
	if (*end && (*end != 'f' || *(end + 1))) {
		std::cout << "invalid input\n";
		return;
	}

	if (f != f || f == 1.0f / 0.0f || f == -1.0f / 0.0f) {
		std::cout << "char: impossible\n";
		std::cout << "int: impossible\n";
	} else {
		char c = static_cast<char>(f);
		if (std::isprint(c))
			std::cout << "char: '" << c << "'\n";
		else
			std::cout << "char: non displayable\n";
		std::cout << "int: " << static_cast<int>(f) << "\n";
	}

	if (f != f)
		std::cout << "float: nanf\n";
	else if (f == 1.0f / 0.0f)
		std::cout << "float: inff\n";
	else if (f == -1.0f / 0.0f)
		std::cout << "float: -inff\n";
	else
		std::cout << "float: " << f << "f\n";

	std::cout << "double: " << static_cast<double>(f) << "\n";
}

void ScalarConverter::convertDouble(const std::string& input) {
	std::cout << "===Convert Double===\n";
	std::cout << std::fixed << std::setprecision(2);

	char *end;
	double d = std::strtod(input.c_str(), &end);
	if (*end) {
		std::cout << "invalid input\n";
		return;
	}

	if (d != d || d == 1.0 / 0.0 || d == -1.0 / 0.0) {
		std::cout << "char: impossible\n";
		std::cout << "int: impossible\n";
	} else {
		char c = static_cast<char>(d);
		if (std::isprint(c))
			std::cout << "char: '" << c << "'\n";
		else
			std::cout << "char: non displayable\n";
		std::cout << "int: " << static_cast<int>(d) << "\n";
	}

	if (d != d)
		std::cout << "float: nanf\n";
	else if (d == 1.0 / 0.0)
		std::cout << "float: inff\n";
	else if (d == -1.0 / 0.0)
		std::cout << "float: -inff\n";
	else
		std::cout << "float: " << static_cast<float>(d) << "f\n";

	if (d != d)
		std::cout << "double: nan\n";
	else if (d == 1.0 / 0.0)
		std::cout << "double: inf\n";
	else if (d == -1.0 / 0.0)
		std::cout << "double: -inf\n";
	else
		std::cout << "double: " << d << "\n";
}

void ScalarConverter::convertInt(const std::string& input) {
	std::cout << "===Convert Int===\n";
	std::cout << std::fixed << std::setprecision(2);

	char *end;
	long n = std::strtol(input.c_str(), &end, 10);
	if (*end) {
		std::cout << "invalid input\n";
		return;
	}

	if (n > std::numeric_limits<int>::max() || n < std::numeric_limits<int>::min()) {
		std::cout << "char: impossible\n";
		std::cout << "int: impossible\n";
		std::cout << "float: impossible\n";
	} else {
		char c = static_cast<char>(n);
		if (std::isprint(c))
			std::cout << "char: '" << c << "'\n";
		else
			std::cout << "char: non displayable\n";
		std::cout << "int: " << static_cast<int>(n) << "\n";
	}
	// std::cout << "float: " << static_cast<float>(n) << "f\n";
	std::cout << "double: " << static_cast<double>(n) << "\n";
}

void ScalarConverter::convert(const std::string& input) {
	if (input.length() == 1 && !std::isdigit(input[0])) {
		convertChar(input);
		return;
	}
	else if (
		input == "nanf" || input == "+inff" || input == "-inff" ||
		(input.length() > 1 && input[input.length() - 1] == 'f' && input.find('.') != std::string::npos &&
		(std::isdigit(input[0]) || input[0] == '-' || input[0] == '+'))
	) {
		convertFloat(input);
		return;
	}
	else if (
		input == "nan" || input == "+inf" || input == "-inf" ||
		(input.find('.') != std::string::npos &&
		(std::isdigit(input[0]) || input[0] == '-' || input[0] == '+'))
	) {
		convertDouble(input);
		return;
	}
	else if (input.find('.') == std::string::npos &&
		input.find('f') == std::string::npos &&
		(std::isdigit(input[0]) || input[0] == '-' || input[0] == '+')) {
		convertInt(input);
		return;
	}
	std::cout
		<< "===Invalid Input===\n";
}
