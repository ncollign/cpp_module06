#include "Helpers.hpp"
#include "ScalarConverter.hpp"

bool isPrintableChar(int x) {
    return (x >= 32 && x <= 126 && x != 127);
}

bool isFiniteDouble(double d) {
    const double PINF = std::numeric_limits<double>::infinity();
    return (d == d) && (d != PINF) && (d != -PINF);
}

bool isIntegralDouble(double d) {
    if (!isFiniteDouble(d))
		return false;

    double ip;
    double frac = std::modf(d, &ip);

    return (std::fabs(frac) == 0.0);
}

void printFixedOne(const char* label, double value, bool asFloat) {
    std::ios::fmtflags oldf = std::cout.flags();
    std::streamsize oldp = std::cout.precision();

    std::cout.setf(std::ios::fixed);
    std::cout.precision(1);

    std::cout << label << ": " << value;
    if (asFloat) std::cout << "f";
    std::cout << "\n";

    std::cout.flags(oldf);
    std::cout.precision(oldp);
}

void ScalarPrinter::printAllFromInt(long n, bool inRange) {
    // ---- char ----
    // test cas impossibles
    if (!inRange || n < 0 || n > 127) {
        std::cout << "char: impossible\n";
    } else {
        char c = static_cast<char>(n);
        if (!isPrintableChar(static_cast<int>(c))) {
            std::cout << "char: Non displayable\n";
        } else {
            std::cout << "char: '" << c << "'\n";
        }
    }

    // ---- int ----
    if (!inRange) {
        std::cout << "int: impossible\n";
    } else {
        std::cout << "int: " << static_cast<int>(n) << "\n";
    }

    // ---- float ----
    printFixedOne("float", static_cast<double>(static_cast<float>(n)), true);

    // ---- double ----
    printFixedOne("double", static_cast<double>(n), false);
}

void ScalarPrinter::printAllFromChar(char c) {
    // ---- char ----
    if (!isPrintableChar(static_cast<unsigned char>(c))) {
        std::cout << "char: Non displayable\n";
    } else {
        if (c == '\'' || c == '\\')
            std::cout << "char: '" << '\\' << c << "'\n";
        else
            std::cout << "char: '" << c << "'\n";
    }

    // ---- int ----
    std::cout << "int: " << static_cast<int>(c) << "\n";

    // ---- float ----
    std::cout << "float: " << static_cast<float>(c) << ".0f\n";

    // ---- double ----
    std::cout << "double: " << static_cast<double>(c) << ".0\n";
}

void ScalarPrinter::printAllFromPseudo(bool isFloat, int sign) {
	std::cout << "char: impossible\n";
	std::cout << "int: impossible\n";

	// float / double : on affiche selon le signe
	if (isFloat) {
		if (sign == 0)
			std::cout << "float: nanf\n";
		else if (sign > 0)
			std::cout << "float: +inff\n";
		else
			std::cout << "float: -inff\n";

		// La version double correspondante
		if (sign == 0)
			std::cout << "double: nan\n";
		else if (sign > 0)
			std::cout << "double: +inf\n";
		else
			std::cout << "double: -inf\n";
	}
	else {
		if (sign == 0)
			std::cout << "float: nanf\n";
		else if (sign > 0)
			std::cout << "float: +inff\n";
		else
			std::cout << "float: -inff\n";

		if (sign == 0)
			std::cout << "double: nan\n";
		else if (sign > 0)
			std::cout << "double: +inf\n";
		else
			std::cout << "double: -inf\n";
	}
}

void ScalarPrinter::printAllFromFloat(float f) {
    const float PINF = std::numeric_limits<float>::infinity();
    const bool  isNaN = (f != f);
    const bool  isInf = (f == PINF || f == -PINF);

    // ---- char ----
    if (isNaN || isInf || f < 0.0f || f > 127.0f) {
        std::cout << "char: impossible\n";
    } else {
        int ci = static_cast<int>(f);
        if (!isPrintableChar(ci)) std::cout << "char: Non displayable\n";
        else                      std::cout << "char: '" << static_cast<char>(ci) << "'\n";
    }

    // ---- int ----
    if (isNaN || isInf || f < static_cast<float>(INT_MIN) || f > static_cast<float>(INT_MAX)) {
        std::cout << "int: impossible\n";
    } else {
        std::cout << "int: " << static_cast<int>(f) << "\n";
    }

    // ---- float ----
    if (isNaN) {
        std::cout << "float: nanf\n";
    } else if (isInf) {
        std::cout << "float: " << (f < 0 ? "-inff\n" : "+inff\n");
    } else {
        // normaliser -0.0f -> 0.0f
        float out = (std::fabs(f) == 0.0f) ? 0.0f : f;
        if (isIntegralDouble(static_cast<double>(f)))
    		printFixedOne("float", static_cast<double>(out), true);
        else
            std::cout << "float: " << out << "f\n";
    }

    // ---- double ----
    double d = static_cast<double>(f);
    if (isNaN) {
        std::cout << "double: nan\n";
    } else if (isInf) {
        std::cout << "double: " << (d < 0 ? "-inf\n" : "+inf\n");
    } else {
        double out = (std::fabs(d) == 0.0) ? 0.0 : d;
        if (isIntegralDouble(d))
            printFixedOne("double", out, false);
        else
            std::cout << "double: " << out << "\n";
    }
}

void ScalarPrinter::printAllFromDouble(double d) {
    // --- états spéciaux ---
    const double PINF = std::numeric_limits<double>::infinity();
    const bool   isNaN = (d != d);
    const bool   isInf = (d == PINF || d == -PINF);

    // ---- char ----
    if (isNaN || isInf || d < 0.0 || d > 127.0) {
        std::cout << "char: impossible\n";
    } else {
        int ci = static_cast<int>(d);
        if (!isPrintableChar(ci)) std::cout << "char: Non displayable\n";
        else                      std::cout << "char: '" << static_cast<char>(ci) << "'\n";
    }

    // ---- int ----
    if (isNaN || isInf || d < static_cast<double>(INT_MIN) || d > static_cast<double>(INT_MAX)) {
        std::cout << "int: impossible\n";
    } else {
        std::cout << "int: " << static_cast<int>(d) << "\n";
    }

    // ---- float ----
    {
        float f = static_cast<float>(d);
        const float FPINF = std::numeric_limits<float>::infinity();
        const bool  fNaN  = (f != f);
        const bool  fInf  = (f == FPINF || f == -FPINF);

        if (fNaN) {
            std::cout << "float: nanf\n";
        } else if (fInf) {
            std::cout << "float: " << (f < 0 ? "-inff\n" : "+inff\n");
        } else {
            // normaliser -0.0f
            float out = (std::fabs(f) == 0.0f) ? 0.0f : f;
            if (isIntegralDouble(static_cast<double>(f)))
    			printFixedOne("float", static_cast<double>(out), true);
            else
                std::cout << "float: " << out << "f\n";
        }
    }

    // ---- double ----
    if (isNaN) {
        std::cout << "double: nan\n";
    } else if (isInf) {
        std::cout << "double: " << (d < 0 ? "-inf\n" : "+inf\n");
    } else {
        double out = (std::fabs(d) == 0.0) ? 0.0 : d;
        if (isIntegralDouble(d))
            printFixedOne("double", out, false);
        else
            std::cout << "double: " << out << "\n";
    }
}
