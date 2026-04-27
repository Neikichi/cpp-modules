#include <iostream>
#include "Array.hpp"

template <typename T>
Array<T>::Array() : _arr(NULL), _size(0) {}

template <typename T>
Array<T>::Array(unsigned int n) : _arr(new T[n]), _size(n) {}

template <typename T>
Array<T>::Array(const Array& other) : _arr(new T[other._size]), _size(other._size) {
	for (unsigned int i = 0; i < _size; i++)
		_arr[i] = other._arr[i];
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
	if (this != &other) {
		delete[] this->_arr;
		this->_size = other._size;
		this->_arr = new T[other._size];
		for (unsigned int i = 0; i < other._size; ++i)
			this->_arr[i] = other._arr[i];
	}
	return *this;
}

template <typename T>
Array<T>::~Array() {
	delete[] this->_arr;
}

template <typename T>
T& Array<T>::operator[](unsigned int idx) {
	if (idx >= this->_size)
		throw std::out_of_range("Index out of range");
	return this->_arr[idx];
}

template <typename T>
const T& Array<T>::operator[](unsigned int idx) const {
	if (idx >= this->_size)
		throw std::out_of_range("Index out of range");
	return this->_arr[idx];
}

template <typename T>
unsigned int Array<T>::size() const {
	return this->_size;
}
