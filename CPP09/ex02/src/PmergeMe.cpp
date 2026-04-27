#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include <sys/time.h>
#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _varr(0), _darr(0) {}

PmergeMe::PmergeMe(const PmergeMe& other) : _varr(other._varr), _darr(other._darr) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	if (this != &other) {
		this->_varr = other._varr;
		this->_darr = other._darr;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

template <typename T>
std::string ctToStr(const T& c) {
	const std::string sep = " ";

    std::ostringstream oss;
    typename T::const_iterator it = c.begin();
    if (it != c.end()) {
        oss << *it;
        ++it;
    }
    for (; it != c.end(); ++it) {
        oss << sep << *it;
    }
    return oss.str();
}

bool PmergeMe::checkAndLoadInput(const std::string& s) {
	if (s.find("-") != std::string::npos)
		return false;

	std::stringstream ss(s);
	std::string token;

	while (ss >> token) {
		std::stringstream tss(token);
		std::size_t val;
		char leftover;

		if (!(tss >> val) || (tss >> leftover))
			return false;
		_varr.push_back(val);
		_darr.push_back(val);
	}
	return !s.empty();
}

std::vector<std::size_t> genJacobs(const std::size_t n) {
	std::vector<std::size_t> iSeq, jSeq;
	if (n < 1)
		return iSeq;
	if (n == 1) {
		iSeq.push_back(0);
		return iSeq;
	}

	jSeq.push_back(1);
	std::size_t j0 = 0, j1 = 1, jval;
	while (true) {
		jval = j1 + 2 * j0;
		if (jval >= n)
			break;
		if (jval != jSeq.back())
			jSeq.push_back(jval);
		j0 = j1;
		j1 = jval;
	}

	iSeq.insert(iSeq.end(), jSeq.begin(), jSeq.end());

	for (std::size_t i = n; i-- > 0;) {
		// if (std::find(jSeq.begin(), jSeq.end(), i) == jSeq.end())
		if (!std::binary_search(jSeq.begin(), jSeq.end(), i))
			iSeq.push_back(i);
	}
	return iSeq;
}

template <typename T>
T mergeInsertion(const T& ct) {

	if (ct.size() < 2)
		return ct;
	

	T a, b;
	
	for (std::size_t i = 0; i + 1 < ct.size(); i += 2) {
		if (ct[i] >= ct[i + 1]) {
			a.push_back(ct[i]);
			b.push_back(ct[i + 1]);
		}
		else {
			a.push_back(ct[i + 1]);
			b.push_back(ct[i]);
		} 
	}
	if (ct.size() % 2 != 0)
		a.push_back(ct.back());

	a = mergeInsertion(a);

	std::vector<std::size_t> jseq = genJacobs(b.size());
	for (std::vector<std::size_t>::iterator it = jseq.begin(); it != jseq.end(); ++it) {
		typename T::iterator pos = std::lower_bound(a.begin(), a.end(), b[*it]);
		a.insert(pos, b[*it]);
	}
	return a;
}

void PmergeMe::cpuTimeRun(const std::string& s) {
	std::clock_t st, end;

	st = std::clock();
	_varr = mergeInsertion(_varr);
	end = std::clock();
	double vec_ms = static_cast<double>(end - st) / CLOCKS_PER_SEC * 1000.0;


	st = std::clock();
	_darr = mergeInsertion(_darr);
	end = std::clock();
	double deq_ms = static_cast<double>(end - st) / CLOCKS_PER_SEC * 1000.0;


	std::cout
		<< "===CPU Time Run===\n"
		<< "Before: " << s << "\n"
		<< "After: " << ctToStr(_varr) << "\n" 
		<< "Time to process a range of " << _varr.size() << " elements with std::vector : " << vec_ms << " ms\n"
		<< "Time to process a range of " << _darr.size() << " elements with std::deque : " << deq_ms << " ms\n"
		<< std::endl;
}

void PmergeMe::realTimeRun(const std::string& s) {
	struct timeval st, end;

	gettimeofday(&st, NULL);
	_varr = mergeInsertion(_varr);
	gettimeofday(&end, NULL);

	double vec_ms = (end.tv_sec - st.tv_sec) * 1000.0 + (end.tv_usec - st.tv_usec) / 1000.0;


	gettimeofday(&st, NULL);
	_varr = mergeInsertion(_varr);
	gettimeofday(&end, NULL);

	double deq_ms = (end.tv_sec - st.tv_sec) * 1000.0 + (end.tv_usec - st.tv_usec) / 1000.0;

	std::cout
		<< "===Real Time Run===\n"
		<< "Before: " << s << "\n"
		<< "After: " << ctToStr(_varr) << "\n" 
		<< "Time to process a range of " << _varr.size() << " elements with std::vector : " << vec_ms << " ms\n"
		<< "Time to process a range of " << _darr.size() << " elements with std::deque : " << deq_ms << " ms\n"
		<< std::endl;
}

void PmergeMe::run(const std::string& s) {
	if (!checkAndLoadInput(s))
		throw std::runtime_error("Error: only accept positive value");
	
	cpuTimeRun(s);
	realTimeRun(s);
}
