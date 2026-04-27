#include <iostream>
#include "Point.hpp"
#include "Fixed.hpp"
#include "BSP.hpp"

Point::Point() : x(0), y(0) {}

Point::Point(const float x, const float y) : x(x), y(y) {}

Point::~Point() {}

Point::Point(const Point& other) : x(other.x), y(other.y) {}

Point& Point::operator=(const Point& other) {
	static_cast<void>(other);
	return *this;
}

const Fixed& Point::getX() const {
	return this->x;
}

const Fixed& Point::getY() const {
	return this->y;
}
