#include <iostream>
#include <ostream>
#include "Serializer.hpp"

int main()
{
	{
		std::cout << "===Serializer===" << std::endl;
		Data ptr = {"42KL", 42};

		std::cout
			<< "Original Data address: " << &ptr << std::endl;
		std::cout
			<< "Original Data values: " << ptr.str << ", " << ptr.val << std::endl;

		uintptr_t serial = Serializer::serialize(&ptr);

		std::cout
			<< "Serialized (uintptr_t): " << serial << std::endl;

		Data* deserial = Serializer::deserialize(serial);

		std::cout
			<< "Deserialized Data address: " << deserial << std::endl;
		std::cout
			<< "Deserialized Data values: " << deserial->str << ", " << deserial->val << std::endl;

		if (deserial == &ptr)
			std::cout << "✅ Pointer match: Deserialization successful!" << std::endl;
		else
			std::cout << "❌ Pointer mismatch: Something went wrong!" << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << "===Serializer: NULL===" << std::endl;
		Data* ptr_null = NULL;

		std::cout
			<< "Original Data address: " << &ptr_null << std::endl;
		// std::cout
		// 	<< "Original Data values: " << ptr.str << ", " << ptr.val << std::endl;

		uintptr_t serial_null = Serializer::serialize(ptr_null);

		std::cout
			<< "Serialized (uintptr_t): " << serial_null << std::endl;

		Data* deserial_null = Serializer::deserialize(serial_null);

		std::cout
			<< "Deserialized Data address: " << deserial_null << std::endl;
		// std::cout
		// 	<< "Deserialized Data values: " << deserial_null->str << ", " << deserial_null->val << std::endl;

		if (deserial_null == ptr_null)
			std::cout << "✅ Pointer match: Deserialization successful!" << std::endl;
		else
			std::cout << "❌ Pointer mismatch: Something went wrong!" << std::endl;

		std::cout << std::endl;
	}

	{
		std::cout << "===Serializer: Dangling Pointer===" << std::endl;
		Data* ptr_dangling = new Data;

		ptr_dangling->str = "Dangling";
		ptr_dangling->val = 42;

		std::cout
			<< "Original Data address: " << &ptr_dangling << std::endl;
		std::cout
			<< "Original Data values: " << ptr_dangling->str << ", " << ptr_dangling->val << std::endl;

		delete ptr_dangling;

		uintptr_t serial_dangling = Serializer::serialize(ptr_dangling);

		std::cout
			<< "Serialized (uintptr_t): " << serial_dangling << std::endl;

		Data* deserial_dangling = Serializer::deserialize(serial_dangling);

		std::cout
			<< "Deserialized Data address: " << deserial_dangling << std::endl;
		// std::cout
		// 	<< "Deserialized Data values: " << deserial_dangling->str << ", " << deserial_dangling->val << std::endl;

		if (deserial_dangling == ptr_dangling)
			std::cout << "✅ Pointer match: Deserialization successful!" << std::endl;
		else
			std::cout << "❌ Pointer mismatch: Something went wrong!" << std::endl;
		std::cout << std::endl;
	}

	return 0;
}

