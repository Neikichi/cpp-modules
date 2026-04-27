#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>

class PmergeMe {
private:
	std::vector<std::size_t> _varr;
	std::deque<std::size_t> _darr;

	bool checkAndLoadInput(const std::string& s);
	void cpuTimeRun(const std::string& s);
	void realTimeRun(const std::string& s);
public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	void run(const std::string& s);
};

#endif
