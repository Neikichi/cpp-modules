#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "EasyFind.hpp"

template <typename T>
typename T::iterator easyfind(T& con, int n) {
	typename T::iterator it = std::find(con.begin(), con.end(), n);

	if (it == con.end()) {
		throw std::runtime_error("Value not found");
	}
	return it;
}
