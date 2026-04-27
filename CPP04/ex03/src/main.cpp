#include "AMateria.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "MateriaSource.hpp"
#include "IMateriaSource.hpp"

int	main(void)
{
	// IMateriaSource* src = new MateriaSource();
	// src->learnMateria(new Ice());
	// src->learnMateria(new Cure());
	// ICharacter* me = new Character("me");
	// AMateria* tmp;
	// tmp = src->createMateria("ice");
	// me->equip(tmp);
	// tmp = src->createMateria("cure");
	// me->equip(tmp);
	// ICharacter* bob = new Character("bob");
	// me->use(0, *bob);
	// me->use(1, *bob);
	//
	// me->equip(src->createMateria("ice"));
	// me->unequip(0);
	//
	// delete bob;
	// delete me;
	// delete src;


	std::cout << "=== Basic setup ===\n";
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	src->learnMateria(NULL);

	ICharacter* me = new Character("me");
	ICharacter* bob = new Character("bob");

	std::cout << "\n=== Equip known materia ===\n";
	me->equip(src->createMateria("ice"));
	me->equip(src->createMateria("cure"));

	std::cout << "\n=== Use materia ===\n";
	me->use(0, *bob); // ice
	me->use(1, *bob); // cure

	std::cout << "\n=== Overfill inventory ===\n";
	me->equip(src->createMateria("ice"));
	me->equip(src->createMateria("cure"));
	me->equip(src->createMateria("ice"));
	me->equip(src->createMateria("cure"));
	me->equip(src->createMateria("ice")); // 5th materia, should fail

	std::cout << "\n=== Use invalid slots ===\n";
	me->use(-1, *bob);
	me->use(4, *bob);

	std::cout << "\n=== Unequip logic ===\n";
	me->unequip(1); // valid
	me->unequip(1); // already empty
	me->unequip(10); // invalid

	std::cout << "\n=== Equip unknown materia ===\n";
	AMateria* unknown = src->createMateria("fire");
	if (!unknown)
		std::cout << "Correctly handled unknown materia.\n";

	std::cout << "\n=== Null equip ===\n";
	me->equip(unknown);
	me->equip(NULL); // should be ignored

	std::cout << "\n=== Assignment operator test ===\n";
	Character dummy("dummy");
	dummy = *(Character*)me; // test assignment
	dummy.use(0, *bob); // should work independently
	dummy.use(0, *bob); // should work independently
	dummy.use(1, *bob); // should work independently

	std::cout << "\n=== Copy constructor test ===\n";
	Character clone(*(Character*)me);
	clone.use(0, *bob);
	clone.use(0, *bob);
	clone.use(1, *bob);

	std::cout << "\n=== Repeated discard test ===\n";
	for (int i = 0; i < 10; ++i) {
		AMateria* mat = src->createMateria("ice");
		me->equip(mat);
		me->unequip(i % 4);
	}

	std::cout << "\n=== Cleanup ===\n";
	delete bob;
	delete me;
	delete src;

	return (0);
}
