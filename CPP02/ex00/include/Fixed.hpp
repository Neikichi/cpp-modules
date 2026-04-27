#ifndef FIXED_HPP
#define FIXED_HPP

class Fixed {
private:
	int	rawVal;
	static const int fracBits = 8;
public:
	Fixed();
	Fixed(int n);
	Fixed(float n);
	Fixed(const Fixed& fixed);
	Fixed& operator=(const Fixed& fixed);
	~Fixed();

	int getRawBits() const;
	void setRawBits(int const raw);
};

#endif
