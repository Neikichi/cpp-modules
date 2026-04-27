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

	bool operator==(const Fixed& other) const;
	bool operator!=(const Fixed& other) const;
	bool operator>=(const Fixed& other) const;
	bool operator<=(const Fixed& other) const;
	bool operator>(const Fixed& other) const;
	bool operator<(const Fixed& other) const;

	Fixed operator+(const Fixed& other) const;
	Fixed operator-(const Fixed& other) const;
	Fixed operator*(const Fixed& other) const;
	Fixed operator/(const Fixed& other) const;

	Fixed& operator++();
	Fixed operator++(int);
	Fixed& operator--();
	Fixed operator--(int);

	int getRawBits() const;
	float toFloat() const;
	int	toInt() const;
	static Fixed& min(Fixed& other1, Fixed& other2);
	static const Fixed& min(const Fixed& other1, const Fixed& other2);
	static Fixed& max(Fixed& other1, Fixed& other2);
	static const Fixed& max(const Fixed& other1, const Fixed& other2);
};

std::ostream& operator<<(std::ostream& COUT, const Fixed& other);

#endif
