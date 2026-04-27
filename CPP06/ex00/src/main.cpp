#include <iostream>
#include "ScalarConverter.hpp"

class Base {
public:
	virtual void speak() const { std::cout << "Base speaking\n"; }
	virtual ~Base() {}
};

class Derived : public Base {
public:
	void speak() const { std::cout << "Derived speaking\n"; }
	void onlyInDerived() const { std::cout << "Unique to Derived\n"; }
};

int main()
{
	std::cout << "=== Static Cast Test ===\n";
	double d = 3.14;
	int i = static_cast<int>(d);  // double to int
	std::cout << "double " << d << " becomes int " << i << "\n";

	Derived dObj;
	Base* bPtr = static_cast<Base*>(&dObj); // upcast
	bPtr->speak();
	dObj.speak();


	std::cout << "\n=== Dynamic Cast Test ===\n";
	Base* basePtr = new Derived();
	Derived* derivedPtr = dynamic_cast<Derived*>(basePtr); // safe downcast
	if (derivedPtr)
		derivedPtr->onlyInDerived();

	Base* wrongBase = new Base();
	Derived* badCast = dynamic_cast<Derived*>(wrongBase); // will return NULL
	if (!badCast)
		std::cout << "dynamic_cast failed (bad downcast)\n";
	delete basePtr;
	delete wrongBase;


	std::cout << "\n=== Reinterpret Cast Test ===\n";
	int* intPtr = new int(65);
	char* charPtr = reinterpret_cast<char*>(intPtr); // treat int* as char*
	std::cout << "First byte of int as char: " << *charPtr << "\n";
	delete intPtr;

	float f = 3.14f;
	int* p = reinterpret_cast<int*>(&f);
	std::cout << "Bit pattern of 3.14: " << *p << "\n";

	// Base* rcb = new Base();
	// Derived* rcd = reinterpret_cast<Derived*>(rcb); // ⚠️ NO — undefined behavior!
	// rcd->onlyInDerived(); // 💥 Might crash — there's no safety check!


	std::cout << "\n=== Const Cast Test ===\n";
	const std::string msg = "Hello";
	std::string& modifiable = const_cast<std::string&>(msg); // dangerous if truly const
	std::cout << "Before change: " << msg << "\n";
	modifiable[0] = 'Y'; // only safe if original wasn't truly const
	std::cout << "After change:  " << msg << "\n";

	
	
	std::cout << "\n=== ScalarConverter Char ===\n";
	ScalarConverter::convert("a");
	ScalarConverter::convert("Z");
	ScalarConverter::convert("!");
	ScalarConverter::convert(" ");
	ScalarConverter::convert("\n");  // non-printable
	ScalarConverter::convert("1");   // digit (should be int, not char)

	std::cout << "\n=== ScalarConverter Int ===\n";
	ScalarConverter::convert("0");
	ScalarConverter::convert("-42");
	ScalarConverter::convert("+123");
	ScalarConverter::convert("2147483647");   // INT_MAX
	ScalarConverter::convert("-2147483648");  // INT_MIN
	ScalarConverter::convert("9999999999");   // overflow
	ScalarConverter::convert("42abc");        // invalid

	std::cout << "\n=== ScalarConverter Float ===\n";
	ScalarConverter::convert("3.14f");
	ScalarConverter::convert("-0.01f");
	ScalarConverter::convert("+42.0f");
	ScalarConverter::convert("nanf");
	ScalarConverter::convert("+inff");
	ScalarConverter::convert("-inff");
	ScalarConverter::convert("123f");         // no dot
	ScalarConverter::convert("3.14.15f");     // invalid

	std::cout << "\n=== ScalarConverter Double ===\n";
	ScalarConverter::convert("3.14");
	ScalarConverter::convert("-0.0001");
	ScalarConverter::convert("+42.0");
	ScalarConverter::convert("nan");
	ScalarConverter::convert("+inf");
	ScalarConverter::convert("-inf");
	ScalarConverter::convert("123.");         // valid double
	ScalarConverter::convert("3.14.15");      // invalid

	std::cout << "\n=== ScalarConverter Invalid ===\n";
	ScalarConverter::convert("");
	ScalarConverter::convert("abc");
	ScalarConverter::convert(".f");
	ScalarConverter::convert("..");
	ScalarConverter::convert("--42");

	return 0;
}

