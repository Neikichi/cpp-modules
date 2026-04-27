#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>

class Zombie {
private:
	std::string name;
public:
	Zombie();
	Zombie(std::string name);
	Zombie& operator=(const Zombie& other);
	~Zombie();
	
	void announce(void);
};

#endif
