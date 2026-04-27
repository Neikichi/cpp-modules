#include <iostream>

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
		return (1);
	}
	for (int i = 1; i < ac; i++)
	{
		std::string str = av[i];
		for (size_t j = 0; j < str.length(); j++)
			str[j] = std::toupper(static_cast<unsigned char>(str[j]));
		std::cout << str;
	}
	std::cout << std::endl;
	return (0);
}
