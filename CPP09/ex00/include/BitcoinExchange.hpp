#ifndef BTC_HPP
#define BTC_HPP

#include <iostream>
#include <map>

#define WHITESPACES " \t\n\r\v\f"

class BitcoinExchange {
private:
	std::map<std::string, float> _db;

	bool ss_split(std::pair<std::string, float>& p, const std::string& s, const std::string& c);
	void matchDB(std::pair<std::string, float>& p) const;
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();
	
	void loadDB(const std::string& path);
	void checkInput(const std::string& path);
	void printDB() const;
};

#endif
