#pragma once
#include<string>
struct DBTable {
	virtual std::string getInsertValues() = 0;
	virtual std::string getSearchValue() = 0;
};
