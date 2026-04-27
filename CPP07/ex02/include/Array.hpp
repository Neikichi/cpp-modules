#ifndef ARRAY_HPP
#define ARRAY_HPP

template <typename T>
class Array {
private:
	T* _arr;
	unsigned int _size;
public:
	Array();
	Array(unsigned int n);
	Array(const Array& other);
	Array& operator=(const Array& other);
	~Array();

	typedef T value_type;
	T& operator[](unsigned int idx);
	const T& operator[](unsigned int idx) const;
	unsigned int size() const;
};

#include "Array.tpp"

#endif
