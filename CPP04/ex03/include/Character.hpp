#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "AMateria.hpp"
#include "ICharacter.hpp"

class Character : public ICharacter {
private:
	const std::string _name;
	const static int _slotsSize = 4;
	AMateria* _slots[_slotsSize];

	AMateria** _trashCan;
	int _trashCanSize;
	void discard(AMateria*);
public:
	Character(const std::string& name);
	Character(const Character& other);
	Character& operator=(const Character& other);
	~Character();

	const std::string& getName() const;
	void equip(AMateria* m);
	void unequip(int idx);
	void use(int idx, ICharacter& target);
};

#endif
