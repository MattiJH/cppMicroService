#include "location.hpp"
std::string Location::getValues()
{
	std::string helperValue;

	helperValue = std::to_string(id);
	helperValue += ",\"" + name + '"';
	helperValue += ",\"" + address + '"';
	helperValue += ",\"" + city + '"';
	helperValue += "," + std::to_string(zip);
	helperValue += ",\"" + country + '"';
	return helperValue;
}
