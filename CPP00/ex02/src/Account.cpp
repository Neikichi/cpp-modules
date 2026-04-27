#include <iostream>
#include "Account.hpp"
#include <ctime>

Account::Account(int initial_deposit) {
	this->_accountIndex = Account::_nbAccounts;
	this->_amount = initial_deposit;
	this->_nbDeposits = 0;
	this->_nbWithdrawals = 0;
	Account::_nbAccounts++;
	Account::_totalAmount += initial_deposit;

	Account::_displayTimestamp();
	std::cout
		<< "index:" << this->_accountIndex
		<< ";amount:" << initial_deposit
		<< ";created\n";
}

Account::~Account() {}

void Account::displayAccountsInfos() {
	Account::_displayTimestamp();
	std::cout
		<< "accounts:" << Account::_nbAccounts
		<< ";total:" << Account::_totalAmount
		<< ";deposits:" << Account::_totalNbDeposits
		<< ";withdrawals:" << Account::_totalNbWithdrawals
		<< "\n";
}

void Account::_displayTimestamp() {
	char buf[20];
	std::time_t now = std::time(NULL);
	std::tm* tm = std::localtime(&now);
	std::strftime(buf, sizeof(buf), "[%Y%m%d_%H%M%S] ", tm);
	std::cout << buf;
}

void Account::displayStatus() const {
	Account::_displayTimestamp();
	std::cout
		<< "index:" << this->_accountIndex
		<< ";amount:" << this->_amount
		<< ";deposits:" << this->_nbDeposits
		<< ";withdrawals:" << this->_nbWithdrawals
		<< "\n";
}

void Account::makeDeposit(int deposits) {
	int p_amt = this->_amount;
	this->_amount += deposits;
	this->_nbDeposits++;
	Account::_totalAmount += deposits;
	Account::_totalNbDeposits++;

	Account::_displayTimestamp();
	std::cout
		<< "index:" << this->_accountIndex
		<< ";p_amount:" << p_amt
		<< ";deposits:" << deposits
		<< ";amount:" << this->_amount
		<< ";nb_deposits:" << this->_nbDeposits
		<< "\n";
}

bool Account::makeWithdrawal(int withdrawal) {
	int p_amt = this->_amount;
	this->_amount -= withdrawal;
	this->_nbDeposits++;
	Account::_totalAmount += deposits;
	Account::_totalNbDeposits++;

	Account::_displayTimestamp();
	std::cout
		<< "index:" << this->_accountIndex
		<< ";p_amount:" << p_amt
		<< ";deposits:" << deposits
		<< ";amount:" << this->_amount
		<< ";nb_deposits:" << this->_nbDeposits
		<< "\n";
	
}
