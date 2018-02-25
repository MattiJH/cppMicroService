#pragma once

#include <string>
#include <vector>
#include "location.hpp"
class Dao {
public:
	bool insertIntoDB(Location& add);
	std::vector<Location> getAllFromDB();

private:
	int determineID();
};

