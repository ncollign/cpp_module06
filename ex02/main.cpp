#include <iostream>
#include "factory.hpp"
#include "identify.hpp"
#include "A.hpp"

int main() {
	for (int i = 0; i < 5; ++i) {
		Base* p = generate();

		std::cout << "Test #" << i+1 << "\n";
		std::cout << "identify(Base*): ";
		identify(p);

		std::cout << "identify(Base&): ";
		identify(*p);

		std::cout << "-----------------------\n";
		delete p;
	}

	std::cout << "-----------------------\n";
	Base* z = 0;
	identify(z);
	delete(z);

	std::cout << "-----------------------\n";
	A a;
	Base& r = a;
	identify(&a);
	identify(r);

	std::cout << "-----------------------\n";

	Base b;
	identify(&b);
	identify(b);
	std::cout << "-----------------------\n";
	
	return (0);
}