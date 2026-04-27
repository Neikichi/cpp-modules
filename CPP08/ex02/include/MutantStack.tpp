#include <iostream>
#include <stack>
#include "MutantStack.hpp"

template<typename T>
MutantStack<T>::MutantStack() {}

template<typename T>
MutantStack<T>::MutantStack(const MutantStack& other) : std::stack<T>(other) {}

template<typename T>
MutantStack<T>& MutantStack<T>::operator=(const MutantStack& other) {
	if (this != &other) {
		std::stack<T>::operator=(other);
	}
	return *this;
}

template<typename T>
MutantStack<T>::~MutantStack() {}

template<typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin() {
	return this->c.begin();
}

template<typename T>
typename MutantStack<T>::iterator MutantStack<T>::end() {
	return this->c.end();
}

template<typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::begin() const {
	return this->c.begin();
}

template<typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::end() const {
	return this->c.end();
}

// template<typename T>
// void MutantStack<T>::push(const T& v) {
// 	this->_stack.push(v);
// }
//
// template<typename T>
// void MutantStack<T>::pop() {
// 	this->_stack.pop();
// }
//
// template<typename T>
// T& MutantStack<T>::top() {
// 	return this->_stack.top();
// }
//
// template<typename T>
// const T& MutantStack<T>::top() const {
// 	return this->_stack.top();
// }
//
// template<typename T>
// bool MutantStack<T>::empty() const {
// 	return this->_stack.empty();
// }
//
// template<typename T>
// std::size_t MutantStack<T>::size() const {
// 	return this->_stack.size();
// }
