#include "dao.hpp"
#include <SQLiteCpp\SQLiteCpp.h>
#include <iostream>


int Dao::determineID() {
	SQLite::Database db("testDB.db");
	SQLite::Statement query(db, "SELECT Location_id FROM Location ORDER BY Location_id ASC");

	int id = NULL;
	while (query.executeStep()) {
		if (id + 1 == (int)query.getColumn(0)) {
			id = query.getColumn(0);
		}
		else {
			break;
		}
	}
	return id + 1;
}
bool Dao::insertIntoDB(Location& add) {
	bool success = true;
	try
	{
		SQLite::Database db("testDB.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

		add.id = determineID();
		SQLite::Transaction transaction(db);
		std::string query = "INSERT INTO Location(Location_id, Location_name, Street_address, City, Zip, Country) VALUES(";
		query += add.getInsertValues();
		query += ")";
		std::cout << query << std::endl;
		db.exec(query);
		transaction.commit();
	}
	catch (std::exception& e)
	{
		success = false;
		std::cout << "exception: " << e.what() << std::endl;
	}
	return success;
}
	bool Dao::updateDB(Location& update) {
		bool success = true;
		try
		{
			SQLite::Database db("testDB.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

			
			SQLite::Transaction transaction(db);
			std::string query = "UPDATE Location SET ";
			query += "Location_name = \"" + update.name +'"';
			query += ",Street_address = \"" + update.address + '"';
			query += ",City = \"" + update.city + '"'; 
			query += ", Zip = " + std::to_string(update.zip); 
			query += ",Country = \"" + update.country + '"';
			query += "WHERE Location_id = " + std::to_string(update.id);
		
			int rc = db.exec(query);
			transaction.commit();
			if (rc < 1)
				success = false;
		}
		catch (std::exception& e)
		{
			success = false;
			std::cout << "exception: " << e.what() << std::endl;
		}
		return success;
	}


std::vector<Location> Dao::getAllFromDB() {
	std::vector<Location> results;
	try
	{
		
		SQLite::Database db("testDB.db");

		SQLite::Statement query(db, "SELECT * FROM Location");

		while (query.executeStep()) {
			Location add;
			add.id = query.getColumn(0);
			const char* name = query.getColumn(1);
			add.name = name;
			const char* address = query.getColumn(2);
			add.address = address;
			const char* city = query.getColumn(3);
			add.city = city;
			add.zip = query.getColumn(4);
			const char* country = query.getColumn(5);
			add.country = country;
			
			results.push_back(add);
		}
		
	}
	catch (std::exception& e)
	{
		std::cout << "exception: " << e.what() << std::endl;
	}
	return results;
}
std::vector<Location> Dao::getByValue(Location& search) {
	std::vector<Location> results;
	try
	{

		SQLite::Database db("testDB.db");
		std::string searchValue = search.getSearchValue();
		if (searchValue != "")
		{
			SQLite::Statement query(db, "SELECT * FROM Location WHERE " + searchValue);
			

			while (query.executeStep()) {
				Location add;
				add.id = query.getColumn(0);
				const char* name = query.getColumn(1);
				add.name = name;
				const char* address = query.getColumn(2);
				add.address = address;
				const char* city = query.getColumn(3);
				add.city = city;
				add.zip = query.getColumn(4);
				const char* country = query.getColumn(5);
				add.country = country;

				results.push_back(add);
			}
		}
	}
	catch (std::exception& e)
	{
		std::cout << "exception: " << e.what() << std::endl;
	}
	return results;
}

bool Dao::deleteRow(Location& deleteLocation) {
	bool success = true;
	try
	{
		std::string searchValue = deleteLocation.getSearchValue();

		if (searchValue != "")
		{

		SQLite::Database db("testDB.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
		SQLite::Transaction transaction(db);
		std::string query = "DELETE FROM Location WHERE " + searchValue;

			int rc = db.exec(query);
			transaction.commit();
			if (rc < 1)
				success = false;
		}
	}
	catch (std::exception& e)
	{
		success = false;
		std::cout << "exception: " << e.what() << std::endl;
	}
	return success;
}