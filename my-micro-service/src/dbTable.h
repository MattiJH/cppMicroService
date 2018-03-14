#pragma once
#include<string>

//template class for mapping table
struct DBTable {
	virtual std::string getInsertValues() = 0;
	virtual std::string getSearchValue() = 0;
};
