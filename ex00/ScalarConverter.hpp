#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <climits>
#include <limits>
#include <cmath>
#include <cfloat>
#include <cctype>

class ScalarConverter {
public:
	static void convert(std::string const &literal);

private:
	ScalarConverter();
	ScalarConverter(ScalarConverter const &);
	ScalarConverter &operator=(ScalarConverter const &);
	~ScalarConverter();

	enum Type {
		T_CHAR,
		T_INT,
		T_FLOAT,
		T_DOUBLE,
		T_PSEUDO,
		T_INVALID
	};

	static Type detectType(std::string const &s);
	static bool isPseudo(std::string const &s);
	static bool isCharLiteral(std::string const &s);
	static bool isIntLiteral(std::string const &s);
	static bool isFloatLiteral(std::string const &s);
	static bool isDoubleLiteral(std::string const &s);
};

#endif
