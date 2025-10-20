#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <climits>
#include <limits>
#include <cmath>
#include <cfloat>
#include <cctype>

bool isPrintableChar(int x);
bool isIntegralDouble(double d);
void printFixedOne(const char* label, double value, bool asFloat);

class ScalarConverter;

namespace ScalarPrinter {
	void printAllFromChar(char c);
	void printAllFromInt(long n, bool inRange);
	void printAllFromFloat(float f);
	void printAllFromDouble(double d);
	void printAllFromPseudo(bool isFloat, int sign);
}

#endif
