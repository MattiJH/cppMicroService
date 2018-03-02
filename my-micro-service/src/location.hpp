
#pragma once
#include<string>
#include <codecvt>
struct Location {

	Location();
	int id;
	std::string name;
	std::string address;
	std::string city;
	int zip;
	std::string country;

	std::string getInsertValues();
	std::string getSearchValue();

};
