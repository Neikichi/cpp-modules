#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <vector>

class Span {
private:
	unsigned int _N;
	unsigned int _size;
	std::vector<unsigned int> _arr;
public:
	Span(unsigned int N);
	Span(const Span& other);
	Span& operator=(const Span& other);
	~Span();

	void addNumber(unsigned int N);
	unsigned int shortestSpan() const;
	unsigned int longestSpan() const;

	void autoRandElement(unsigned int maxVal);
	typedef std::vector<unsigned int>::const_iterator const_iterator;
	bool empty() const;
	std::vector<unsigned int>::const_iterator begin() const;
	std::vector<unsigned int>::const_iterator end() const;
};

#endif
