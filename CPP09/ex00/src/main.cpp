#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include "BitcoinExchange.hpp"

int main(int ac, char** av) {
	if (ac != 2) {
		std::cerr << "Invalid input! Usage: ./btc <path_to_csv>" << std::endl;
		return 1;
	}

	std::string dbPath = "data.csv";

	BitcoinExchange btc;
	(void)av;
	try {
		btc.loadDB(dbPath);
		// btc.printDB();
		btc.checkInput(av[1]);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
