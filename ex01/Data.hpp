#ifndef DATA_HPP
#define DATA_HPP

#include <string>

struct Data {
	std::string name;
	int age;

	Data();
	Data(const std::string &n, int a);
};

#endif