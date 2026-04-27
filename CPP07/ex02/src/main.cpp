#include <cstdlib>
#include <exception>
#include <sstream>
#include "Array.hpp"

int genInt(unsigned int i) {
	return i * 10;
}

float genFloat(unsigned int i) {
	return i * 0.5f;
}

double genDouble(unsigned int i) {
	return i * 0.5;
}

std::string genStr(unsigned int i) {
	std::ostringstream oss;
	oss << "Val #" << i;
	return oss.str();
}

char genChar(unsigned int i) {
	return 'A' + (i % 26);
}

template <typename T>
void autoInsert(T& arr, typename T::value_type (*gen)(unsigned int)) {
	for (unsigned int i = 0; i < arr.size(); ++i) {
		try {
			arr[i] = gen(i);
		}
		catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	autoPrint(arr);
}

template <typename T>
void autoPrint(const T& arr) {
	for (unsigned int i = 0; i < arr.size(); ++i)
		std::cout << "arr[" << i <<"] = " << arr[i] << std::endl;
}

#define MAX_VAL 750
void pdfMain() {
	Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    //SCOPE
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
			exit(1);
        }
    }
    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
    delete [] mirror;//
}

void ownTest() {
	Array<int> intArr(4);
	Array<float> floatArr(4);
	Array<double> doubleArr(4);
	Array<std::string> strArr(4);
	Array<char> charArr(4);

	std::cout << "\n===Int===" << std::endl;
	autoInsert(intArr, genInt);
	std::cout << "\n===Float===" << std::endl;
	autoInsert(floatArr, genFloat);
	std::cout << "\n===Double===" << std::endl;
	autoInsert(doubleArr, genDouble);
	std::cout << "\n===String===" << std::endl;
	autoInsert(strArr, genStr);
	std::cout << "\n===Char===" << std::endl;
	autoInsert(charArr, genChar);

	std::cout << "\n===Exception===" << std::endl;
	try {
		intArr[5] = 5;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

int main() {

	std::cout << "===Main Test===" << std::endl;
	pdfMain();
	std::cout << "===Own Test===" << std::endl;
	ownTest();
	return 0;
}
