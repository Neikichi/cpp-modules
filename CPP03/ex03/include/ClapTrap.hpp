#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>

class ClapTrap {
protected:
	std::string _name;
	int _hitPoints;
	int _energyPoints;
	int _atkDmg;
public:
	ClapTrap();
	ClapTrap(std::string name);
	ClapTrap(const ClapTrap& other);
	ClapTrap& operator=(const ClapTrap& other);
	virtual ~ClapTrap();

	void attack(const std::string& target);
	void takeDamage(unsigned int amount);
	void beRepaired(unsigned int amount);

	void setName(const std::string name);
	void setHP(unsigned int amount);
	void setEP(unsigned int amount);
	void setAD(unsigned int amount);
	std::string getName() const;
	int getHP() const;
	int	getEP() const;
	int getAD() const;
	void status() const;
};

#endif
