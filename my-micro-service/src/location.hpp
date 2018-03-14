
#pragma once
#include<string>
#include <codecvt>
#include "dbTable.h"

//Mapping struct for Location Table in the DB
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
