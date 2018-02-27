#pragma once

#include <string>
#include <vector>
#include "location.hpp"
class Dao {
public:
	bool insertIntoDB(Location& add);
	bool updateDB(Location& update);
	std::vector<Location> getAllFromDB();
	
private:
	int determineID();
};

