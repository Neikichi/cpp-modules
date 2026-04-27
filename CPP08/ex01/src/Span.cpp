#include <algorithm>
#include <climits>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Span.hpp"

Span::Span(unsigned int N) : _N(N), _size(0), _arr(0) {}

Span::Span(const Span& other) : _N(other._N), _size(other._size), _arr(other._arr) {}

Span& Span::operator=(const Span& other) {
	if (this != &other) {
		this->_N = other._N;
		this->_size = other._size;
		this->_arr = other._arr;
	}
	return *this;
}

Span::~Span() {}

void Span::addNumber(unsigned int N) {
	if (_size > _N)
		throw std::runtime_error("Span is full");
	_arr.push_back(N);
	_size++;
}

unsigned int Span::shortestSpan() const {
	if (_size < 2)
		throw std::runtime_error("Only 1 element in span container");
	std::vector<unsigned int> sorted = this->_arr;
	std::sort(sorted.begin(), sorted.end());

	unsigned int min = UINT_MAX;
	for (size_t i = 1; i < sorted.size(); i++) {
		unsigned int diff = sorted[i] - sorted[i - 1];
		if (diff < min)
			min = diff;
	}
	return min;
}

unsigned int Span::longestSpan() const {
	if (_size < 2)
		throw std::runtime_error("Only 1 element in span container");
	std::vector<unsigned int> sorted = this->_arr;
	std::sort(sorted.begin(), sorted.end());
	return sorted[sorted.size() - 1] - sorted[0];
}

bool Span::empty() const {
	return this->_arr.empty();
}

std::vector<unsigned int>::const_iterator Span::begin() const {
	return this->_arr.begin();
}

std::vector<unsigned int>::const_iterator Span::end() const {
	return this->_arr.end();
}

void Span::autoRandElement(unsigned int maxVal) {
	srand(time(0));
	
	while (_size < _N) {
		this->addNumber(rand() & maxVal);
	}
}
