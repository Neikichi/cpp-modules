#include <iostream>
#include <iomanip>
#include <sstream>
#include "PhoneBook.hpp"
#include "Contact.hpp"

PhoneBook::PhoneBook() {
	idx = -1;
}

PhoneBook::~PhoneBook() {}


static void	printTitle()
{
	std::cout
		<< std::right
		<< std::setw(printSize) << "Index" << " | "
		<< std::setw(printSize) << "First Name" << " | "
		<< std::setw(printSize) << "Last Name" << " | "
		<< std::setw(printSize) << "Nickname" << "\n";
}

std::string	tr_dot(std::string str)
{
	if (str.size() > printSize)
	{
		str.resize(printSize);
		str[printSize - 1] = '.';
	}
	return str;
}

std::string n_to_str(size_t n) {
	std::stringstream str;
	str << n;
	return str.str();
}

void	PhoneBook::printList(size_t idx)
{
	std::cout
		<< std::right
		<< std::setw(printSize) << tr_dot(n_to_str(idx + 1)) << " | "
		<< std::setw(printSize) << tr_dot(contacts[idx].firstName) << " | "
		<< std::setw(printSize) << tr_dot(contacts[idx].lastName) << " | "
		<< std::setw(printSize) << tr_dot(contacts[idx].nickName) << "\n";
}

void	PhoneBook::add() {
	const std::string strs[] = {
		"First Name",
		"Last Name",
		"Nickname",
		"Phone Number",
		"Darkest Secret"
	};

	if (this->idx < contactSize - 1)
		this->idx++;
	else if (this->idx == contactSize - 1)
		this->idx = 0;
	std::string input;
	std::cout
		<< "Adding new contact:-\n";
	for (size_t i = 0; i < sizeof(strs)/sizeof(strs[0]); i++) {
		while (1) {
			std::cout
				<< "Please enter "
				<< strs[i]
				<< " : ";
			std::getline(std::cin, input);
			if (!input.empty())
				break;
		}
		switch(i) {
			case 0:
				this->contacts[this->idx].firstName = input;
				break;
			case 1:
				this->contacts[this->idx].lastName = input;
				break;
			case 2:
				this->contacts[this->idx].nickName = input;
				break;
			case 3:
				this->contacts[this->idx].phoneNumber = input;
				break;
			case 4:
				this->contacts[this->idx].secret = input;
				break;
			default:
				break;
		}
	}
}

void	PhoneBook::printContact(int idx) {
	std::cout
		<< "\nSelected contact id["
		<< idx << "]\n"
		<< "First Name: " << this->contacts[idx].firstName << "\n"
		<< "Last Name: " << this->contacts[idx].lastName << "\n"
		<< "NickName: " << this->contacts[idx].nickName << "\n"
		<< "PhoneNumber: " << this->contacts[idx].phoneNumber << "\n"
		<< "Darkest Secret: " << this->contacts[idx].secret << "\n";
}

void	PhoneBook::search()
{
	printTitle();
	for (size_t i = 0; i < contactSize; i++) {
		printList(i);
	}
	std::cout << "\n";
	std::string input;
	while (1) {
		std::cout
			<< "Please select which contact index [1-8] to display. [0] back to Menu: ";
		std::getline(std::cin, input);

		std::stringstream ss(input);
		int i_input = -1;
		ss >> i_input;

		if (ss.fail() || i_input < 0 || i_input > 8)
		{
			std::cout << "Invalid Input, try again!\n";
			continue;
		}
		if (i_input == 0)
			break;
		printContact(i_input - 1);
		break;
		// return to menu?
	}

}

void	PhoneBook::exit()
{
	std::exit(0);
}
