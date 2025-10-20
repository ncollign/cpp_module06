#include "ScalarConverter.hpp"
#include "Helpers.hpp"

// déclarés mais non définis publiquement pour éviter erreur de compil
ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(ScalarConverter const &) {}
ScalarConverter &ScalarConverter::operator=(ScalarConverter const &) { return *this; }
ScalarConverter::~ScalarConverter() {}

void ScalarConverter::convert(std::string const& s) {
	Type t = detectType(s);

	switch (t) {
		case T_PSEUDO: {
			bool isFloat = !s.empty() && s[s.size()-1] == 'f';
			int sign = 0;

			if (s[0] == '+')
				sign = +1;
			else if (s[0] == '-')
				sign = -1;
			ScalarPrinter::printAllFromPseudo(isFloat, sign);
			break;
		}
		case T_CHAR: {
			ScalarPrinter::printAllFromChar(s[0]);
			break;
		}
		case T_INT: {
			char *end = 0;
			long v = std::strtol(s.c_str(), &end, 10);
			bool inRange = (v >= INT_MIN && v <= INT_MAX);

			ScalarPrinter::printAllFromInt(v, inRange);
			break;
		}
		case T_FLOAT: {
			char *end = 0;
			float f = static_cast<float>(std::strtod(s.c_str(), &end));

			ScalarPrinter::printAllFromFloat(f);
			break;
		}
		case T_DOUBLE: {
			char *end = 0;
			double d = std::strtod(s.c_str(), &end);

			ScalarPrinter::printAllFromDouble(d);
			break;
		}
		default:
			std::cout << "char: impossible\n"
			          << "int: impossible\n"
			          << "float: impossible\n"
			          << "double: impossible\n";
	}
}

bool ScalarConverter::isPseudo(std::string const& s) {
	return (s == "nan" || s == "+inf" || s == "-inf"
		|| s == "nanf" || s == "+inff" || s == "-inff");
}

bool ScalarConverter::isCharLiteral(std::string const& s) {
	return (s.size() == 1 && !std::isdigit(static_cast<unsigned char>(s[0])));
}

bool ScalarConverter::isIntLiteral(std::string const& s) {
	if (s.empty())
		return (false);

	size_t i = 0;
	if (s[i] == '+' || s[i] == '-') {
		if (++i == s.size())
			return (false);
	}

	for (; i < s.size(); ++i) {
		if (!std::isdigit(static_cast<unsigned char>(s[i])))
			return (false);
	}

	return (true);
}

static bool hasOnlyDigits(std::string const& s, size_t from, size_t to) {
	for (size_t i = from; i < to; i++){
		if (!std::isdigit(static_cast<unsigned char>(s[i])))
			return (false);
	}

	return (true);
}

bool ScalarConverter::isFloatLiteral(std::string const& s) {
	if (s.size() < 2 || s[s.size() - 1] != 'f')
		return false;

	std::string core = s.substr(0, s.size()-1);
	if (core.empty())
		return (false);

	size_t i = 0;
	if (core[i] == '+' || core[i] == '-') {
		if (++i == core.size())
			return (false);
	}

	size_t dot = core.find('.');
	if (dot == std::string::npos)
		return (false);
	
	bool leftOk  = (dot == i) || hasOnlyDigits(core, i, dot);

	bool rightOk = true;
	if (dot + 1 < core.size())
		rightOk = hasOnlyDigits(core, dot + 1, core.size());

	bool someDigit = false;
	for (size_t k = i; k < core.size(); ++k)
		if (std::isdigit(static_cast<unsigned char>(core[k]))) {
			someDigit = true;
			break;
		}

	return (leftOk && rightOk && someDigit);
}

bool ScalarConverter::isDoubleLiteral(std::string const& s) {
	if (s.empty())
		return (false);

	if (s[s.size() - 1] == 'f')
		return (false);

	size_t i = 0;
	if (s[i] == '+' || s[i] == '-') {
		if (++i == s.size())
			return (false);
	}

	size_t dot = s.find('.');
	if (dot == std::string::npos)
		return false;

	bool leftOk  = (dot == i) || hasOnlyDigits(s, i, dot);

	bool rightOk = true;
	if (dot + 1 < s.size())
		rightOk = hasOnlyDigits(s, dot + 1, s.size());

	bool someDigit = false;
	for (size_t k = i; k < s.size(); ++k) {
		if (std::isdigit(static_cast<unsigned char>(s[k]))) {
			someDigit = true; break;
		}
	}

	return (leftOk && rightOk && someDigit);
}

ScalarConverter::Type ScalarConverter::detectType(std::string const& s) {
	if (isPseudo(s))
		return (T_PSEUDO);
	if (isCharLiteral(s))
		return (T_CHAR);
	if (isIntLiteral(s))
		return (T_INT);
	if (isFloatLiteral(s))
		return (T_FLOAT);
	if (isDoubleLiteral(s))
		return (T_DOUBLE);
	return (T_INVALID);
}
