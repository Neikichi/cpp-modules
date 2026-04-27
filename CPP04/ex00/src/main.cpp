#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main() {
	{
		std::cout << "\n=====Animal=====\n";
		const Animal* meta = new Animal();
		const Animal* j = new Dog();
		const Animal* i = new Cat();

		std::cout << j->getType() << " " << std::endl;
		std::cout << i->getType() << " " << std::endl;
		i->makeSound(); //will output the cat sound!
		j->makeSound();
		meta->makeSound();
		delete j;
		delete i;
		delete meta;
		std::cout << std::endl;
	}

	{
		std::cout << "\n\n=====WrongAnimal=====\n";
		const WrongAnimal* wmeta = new WrongAnimal();
		const WrongAnimal* wi = new WrongCat();
		std::cout << wi->getType() << " \n";
		wi->makeSound();
		wmeta->makeSound();
		delete wi;
		delete wmeta;
	}
	
	return 0;
}
