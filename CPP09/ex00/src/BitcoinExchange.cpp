#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _db(other._db) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other) {
		this->_db = other._db;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

static bool validDate(const std::string& s) {
	const int mth[] = {
		0, 31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31
	};

	std::string syy, smm, sdd;
	std::stringstream ss(s);
	if (!std::getline(ss, syy, '-') || !std::getline(ss, smm, '-') || !std::getline(ss, sdd))
		return false;

	int yy, mm, dd;
	std::stringstream yss(syy), mss(smm), dss(sdd);
	yss >> yy;
	mss >> mm;
	dss >> dd;
	// std::cout
	// 	<< "yss: " << yss.str() << "\n"
	// 	<< "mss: " << mss.str() << "\n"
	// 	<< "dss: " << dss.str() << std::endl;
	char leftover;
	if (yss.fail() || yss >> leftover ||
		mss.fail() || mss >> leftover ||
		dss.fail() || dss >> leftover)
		return false;

	if (yy < 1900 || yy > 3000 || mm < 1 || mm > 12)
		return false;
	int maxDay = mth[mm];
	if (mm == 2 && ((yy % 4 == 0 && yy % 100 != 0) || (yy % 400 == 0)))
		maxDay = 29;

	if (dd < 1 || dd > maxDay)
		return false;
	return true;
}

bool BitcoinExchange::ss_split(std::pair<std::string, float>& p, const std::string& s, const std::string& c) {
	std::string date, sval;

	std::stringstream ss(s);

	if (!std::getline(ss, date, c[0]) || !std::getline(ss, sval)) {
		std::cerr << "Error: bad input => " << date << std::endl;
		return false;
	}

	if (!validDate(date)) {
		std::cerr << "Error: Invalid Date" << std::endl;
		return false;
	}

	if (sval.empty()) {
		std::cerr << "Error: Invalid Float" << std::endl;
		return false;
	}

	double f;
	std::stringstream fss(sval);
	fss >> f;
	if (fss.fail() || !fss.eof()) {
		std::cerr << "Error: Invalid Float" << std::endl;
		return false;
	}
	
	if (f < 0.0) {
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	if (f > 2147483647.0) {
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}

	p = std::pair<std::string, float>(date, static_cast<float>(f));
	return true;
}

void BitcoinExchange::matchDB(std::pair<std::string, float>& p) const {
	std::map<std::string, float>::const_iterator it = _db.lower_bound(p.first);

	if (it != _db.end() && it->first == p.first) {
		std::cout
			// << "match: " << it->first << " "
			<< p.first << " => " << p.second
			<< " = " << p.second * it->second << std::endl;
	}
	else if (it != _db.begin()) {
		--it;
		std::cout
			// << "nearest: " << it->first << " "
			<< p.first << " => " << p.second
			<< " = " << p.second * it->second << std::endl;
	}
	else {
		std::cerr
			<< "Error: no earlier date found for " << p.first << std::endl;
	}
}

void BitcoinExchange::loadDB(const std::string& path) {
	std::ifstream inFile(path.c_str());
	if (inFile.fail())
		throw std::runtime_error("Error: Failed to open db file");

	std::string line;
	std::getline(inFile, line);
	std::pair<std::string, float> p;
	while (std::getline(inFile, line)) {
		if (!ss_split(p, line, ","))
			continue;
	
		this->_db[p.first] = p.second;
	}
	inFile.close();
}

void BitcoinExchange::checkInput(const std::string& path) {
	std::ifstream inFile(path.c_str());
	if (inFile.fail())
		throw std::runtime_error("Error: Failed to open input file");

	std::string line;
	std::getline(inFile, line);
	std::pair<std::string, float> p;
	while (std::getline(inFile, line)) {
		if (!ss_split(p, line, "|"))
			continue;
		matchDB(p);
	}
	inFile.close();
}

void BitcoinExchange::printDB() const {
	std::map<std::string, float>::const_iterator it = _db.begin();

	for (std::size_t i = 0; it != _db.end(); ++it, i++) {
		std::cout
			<< i << ". [" << it->first
			<< "]: '" << it->second << "'" << std::endl;
	}
}
