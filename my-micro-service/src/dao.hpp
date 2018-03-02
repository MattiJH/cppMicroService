#pragma once

#include <string>
#include <vector>
#include "location.hpp"
class Dao {
public:
	bool insertIntoDB(Location& add);
	bool updateDB(Location& update);
	std::vector<Location> getByValue(Location& search);
	std::vector<Location> getAllFromDB();
	bool deleteRow(Location& deleteLocation);

private:
	int determineID();
};

