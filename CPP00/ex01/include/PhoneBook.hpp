#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <cstddef>
#include <cstdlib>
#include <Contact.hpp>

#define contactSize 8
#define printSize 10

class PhoneBook {
private:
	Contact contacts[contactSize];
	int		idx;
public:
	PhoneBook();
	~PhoneBook();

	void printList(size_t idx);
	void add();
	void search();
	void printContact(int idx);
	void exit();
};

#endif
