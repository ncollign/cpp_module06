#include "factory.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>

static void initRandomOnce() {
	static bool done = false;

	if (!done) {
		std::srand(static_cast<unsigned int>(std::time(0)));
		done = true;
	}
}

Base* generate() {
	initRandomOnce();
	
	int r = std::rand() % 3;
	if (r == 0) return new A();
	if (r == 1) return new B();

	return new C();
}