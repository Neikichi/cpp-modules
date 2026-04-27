#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
template<typename T>
class MutantStack : public std::stack<T> {
// private:
// 	std::stack<T> _stack;
public:
	MutantStack();
	MutantStack(const MutantStack& other);
	MutantStack& operator=(const MutantStack& other);
	~MutantStack();

	typedef typename std::stack<T>::container_type::iterator iterator;
	typedef typename std::stack<T>::container_type::const_iterator const_iterator;

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	// void push(const T&);
	// void pop();
	// T& top();
	// const T& top() const;
	// bool empty() const;
	// std::size_t size() const;
};

#include "MutantStack.tpp"

#endif
