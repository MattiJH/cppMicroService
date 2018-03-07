#pragma once

#include <string>
#include <vector>
#include "location.hpp"
#include "songs.h"
class Dao {
public:
	bool insertIntoDB(Location& add);
	bool updateDB(Location& update);
	std::vector<Location> getByValue(Location& search);
	std::vector<Location> getAllFromLocations();
	bool deleteRow(Location& deleteLocation);

	bool insertIntoDB(Songs& add);
	bool updateDB(Songs& update);
	std::vector<Songs> getByValue(Songs& search);
	std::vector<Songs> getAllFromSongs();
	bool deleteRow(Songs& deleteLocation);

private:
	int determineIDofLocation();
	int determineIDofSongs();
};

