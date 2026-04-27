#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>

class ScalarConverter {
private:
	ScalarConverter();
	ScalarConverter(const ScalarConverter& other);
	ScalarConverter& operator=(const ScalarConverter& other);
	~ScalarConverter();

	static void convertChar(const std::string& str);
	static void convertFloat(const std::string& str);
	static void convertDouble(const std::string& str);
	static void convertInt(const std::string& str);
public:
	static void convert(const std::string& input);
};

#endif
