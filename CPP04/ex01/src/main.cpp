#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main() {
	std::cout << "=====Mandatory Test=====\n";
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	delete j;
	delete i;

	std::cout << "=====Create and fill array=====\n";
	const int size = 100;
	Animal* zoo[size];

	for (int i = 0; i < size; i++) {
		if (i > size / 2)
			zoo[i] = new Cat();
		else
			zoo[i] = new Dog();
	}

	for (int i = 0; i < size; i++)
		delete zoo[i];
	
	std::cout << "=====Eval Test for deep copies=====\n";
	Dog basic;

	Dog tmp = basic;

	return 0;
}
