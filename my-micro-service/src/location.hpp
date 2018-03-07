
#pragma once
#include<string>
#include <codecvt>
#include "dbTable.h"

struct Location : DBTable {

	Location();
	int id;
	std::string name;
	std::string address;
	std::string city;
	int zip;
	std::string country;

	std::string getInsertValues() override;
	std::string getSearchValue() override;

};
