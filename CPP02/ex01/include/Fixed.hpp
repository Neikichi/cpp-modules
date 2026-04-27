#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed {
private:
	int	rawVal;
	static const int fracBits = 8;
public:
	Fixed();
	Fixed(const int n);
	Fixed(const float n);
	Fixed(const Fixed& other);
	Fixed& operator=(const Fixed& other);
	~Fixed();

	int getRawBits() const;
	float toFloat() const;
	int	toInt() const;
};

std::ostream& operator<<(std::ostream& COUT, const Fixed& other);

#endif
