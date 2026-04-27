#include <fstream>
#include <iostream>

int main(int ac, char *av[]) {
	if (ac != 4) {
		std::cerr << "Invalid arguments! Usage: ./sed <filename> <str1> <str2>" << std::endl;
		return (1);
	}

	std::string s1 = av[2];
	std::string s2 = av[3];
	std::string inName = av[1];
	std::string outName = inName + ".replace";

	std::ifstream inFile(inName.c_str());
	if (!inFile.is_open()) {
		std::cerr << "Failed to open infile.\n";
		return 1;
	}

	std::ofstream outFile(outName.c_str());
	if (!outFile.is_open()) {
		std::cerr << "Failed to open outfile.\n";
		return 1;
	}

	std::string line;
	while (std::getline(inFile, line)) {
		std::string temp;
		std::size_t idx = 0;
		std::size_t match = -1;

		while ((match = line.find(s1, idx)) != std::string::npos) {
			temp += line.substr(idx, match - idx);
			temp += s2;
			idx = match + s1.length();
		}

		temp += line.substr(idx);
		outFile << temp << "\n";
	}

	return 0;
}
