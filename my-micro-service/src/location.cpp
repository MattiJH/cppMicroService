#include "location.hpp"


Location::Location() : id{ -1 }, name{ "" }, address{ "" }, city{ "" }, zip{ -1 }, country{ "" } 
{

}
std::string Location::getInsertValues()
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
std::string Location::getSearchValue() {
	std::string helperValue = "";
	if (id != -1)
	{
		helperValue += " Location_id = "+std::to_string(id);
	}

	if (name != "")
	{
		if (helperValue != "") 
		{
			helperValue += " AND ";
		}
		
		helperValue += " Location_name = \"" + name + '"';
		
	}

	if (address != "")
	{
		if (helperValue != "")
		{
			helperValue += " AND ";
		}
		
		helperValue += " Street_address = \"" + address + '"';
		
	}
	if (city != "")
	{
		if (helperValue != "")
		{
			helperValue += " AND ";
		}
		
		helperValue += " City = \"" + city+'"';
		
	}
	if (zip != -1)
	{
		if (helperValue != "")
		{
			helperValue += " AND ";
		}
		
		helperValue += " Zip = " + std::to_string(zip);
		
	}
	if (country != "")
	{
		if (helperValue != "")
		{
			helperValue += " AND ";
		}
	
		helperValue += " Country = \"" + country + '"';
		
	}

	return helperValue;
}
