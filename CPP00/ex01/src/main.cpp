#include <PhoneBook.hpp>
#include <iostream>
#include <cstring>

void	getPrompt(std::string &option) {
	std::cout
		// << "Welcome to 42 Phonebook.\n"
		<< "Plese select the option:\n"
		<< "1. ADD\n"
		<< "2. SEARCH\n"
		<< "3. EXIT\n"
		<< "Please enter selection: ";
	if (!std::getline(std::cin, option)) {
		std::cin.clear();
		exit(1);
	}
}

int main() {
	PhoneBook phoneBook;
	std::string option;

	std::cout << "Welcome to 42 PhoneBook.\n";
	while (1) {
		getPrompt(option);
		if (option == "1")
			phoneBook.add();
		else if (option == "2")
			phoneBook.search();
		else if (option == "3")
			break;
		else
			std::cout << "\nInvalid selection.\n";
	}
	std::cout << "Thanks for using 42 PhoneBook.\n" << "Goodbye!\n" << std::endl;
	phoneBook.exit();
	return 0;
}
