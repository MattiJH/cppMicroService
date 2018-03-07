#pragma once
#include "dbTable.h"

struct Songs : DBTable {

	int song_id;
	std::string song_name;
	std::string artist;
	std::string album;
	std::string length;
	std::string year;
	std::string lyrics;

	Songs();
	std::string getInsertValues() override;
	std::string getSearchValue() override;
	

};