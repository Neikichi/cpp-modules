#include <iostream>
#include "Point.hpp"
#include "Fixed.hpp"
#include "BSP.hpp"

static Fixed getArea(const Point& p1, const Point& p2, const Point& p3) {
	return ((p1.getX() - p3.getX()) * (p2.getY() - p3.getY()) -
	        (p2.getX() - p3.getX()) * (p1.getY() - p3.getY()));
}

bool bsp(Point const a, Point const b, Point const c, Point const point) {
	Fixed total = getArea(a, b, c);
	Fixed a1 = getArea(point, b, c);
	Fixed a2 = getArea(point, c, a);
	Fixed a3 = getArea(point, a, b);

	if (total < Fixed(0)) {
		total = total * Fixed(-1);
		a1 = a1 * Fixed(-1);
		a2 = a2 * Fixed(-1);
		a3 = a3 * Fixed(-1);
	}

	return (a1 > Fixed(0) && a2 > Fixed(0) && a3 > Fixed(0) &&
			(a1 + a2 + a3) == total);
}
