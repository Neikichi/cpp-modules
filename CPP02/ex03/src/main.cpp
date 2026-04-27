#include <iostream>
#include "Point.hpp"
#include "Fixed.hpp"
#include "BSP.hpp"

int main() {
	Point a(0.0f, 0.0f);
	Point b(4.0f, 0.0f);
	Point c(2.0f, 4.0f);

	Point inside(2.0f, 1.0f);
	Point onEdge(2.0f, 0.0f);
	Point atVertex(0.0f, 0.0f);
	Point outside(5.0f, 5.0f);

	std::cout << "Inside:   " << bsp(a, b, c, inside) << std::endl;   // 1
	std::cout << "On Edge:  " << bsp(a, b, c, onEdge) << std::endl;   // 0
	std::cout << "At Vertex:" << bsp(a, b, c, atVertex) << std::endl; // 0
	std::cout << "Outside:  " << bsp(a, b, c, outside) << std::endl;  // 0

	return 0;
}
