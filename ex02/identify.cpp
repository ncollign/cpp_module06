#include "identify.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <typeinfo>


void identify(Base* p) { // Pointeur
	if (!p) {
		std::cout << "Pointer is null\n";
		return;
	}
	if (dynamic_cast<A*>(p)) {
		std::cout << "A\n";
		return;
	}
	if (dynamic_cast<B*>(p)) {
		std::cout << "B\n";
		return;
	}
	if (dynamic_cast<C*>(p)) {
		std::cout << "C\n";
		return;
	}
	std::cout << "Unknown\n";
}

void identify(Base& p) { // Référence
	try {
		(void)dynamic_cast<A&>(p); std::cout << "A\n"; return;
	} catch (std::bad_cast&) {}
	try {
		(void)dynamic_cast<B&>(p); std::cout << "B\n"; return;
	} catch (std::bad_cast&) {}
	try {
		(void)dynamic_cast<C&>(p); std::cout << "C\n"; return;
	} catch (std::bad_cast&) {}

	std::cout << "Unknown\n";
}