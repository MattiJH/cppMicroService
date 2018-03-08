#include "dao.hpp"
#include <SQLiteCpp\SQLiteCpp.h>
#include <iostream>


int Dao::determineIDofLocation() {
	SQLite::Database db("microServiceDB.db");
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

int Dao::determineIDofSongs() {
	SQLite::Database db("microServiceDB.db");
	SQLite::Statement query(db, "SELECT song_id FROM songs ORDER BY song_id ASC");

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
		SQLite::Database db("microServiceDB.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

		add.id = determineIDofLocation();
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
bool Dao::insertIntoDB(Songs& add) {
	bool success = true;
	try
	{
		SQLite::Database db("microServiceDB.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

		add.song_id = determineIDofSongs();
		SQLite::Transaction transaction(db);
		std::string query = "INSERT INTO songs(song_id, song_name, artist, album, length, year, lyrics) VALUES(";
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
			SQLite::Database db("microServiceDB.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

			
			SQLite::Transaction transaction(db);
			std::string query = "UPDATE Location SET ";
			query += "Location_name = \"" + update.name +'"';
			query += ",Street_address = \"" + update.address + '"';
			query += ",City = \"" + update.city + '"'; 
			query += ", Zip = " + std::to_string(update.zip); 
			query += ",Country = \"" + update.country + '"';
			query += "WHERE Location_id = " + std::to_string(update.id);

			std::cout << query << std::endl;
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

	bool Dao::updateDB(Songs& update) {
		bool success = true;
		try
		{
			SQLite::Database db("microServiceDB.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);


			SQLite::Transaction transaction(db);
			std::string query = "UPDATE songs SET ";
			query += "song_name = \"" + update.song_name + '"';
			query += ", artist = \"" + update.artist + '"';
			query += ", album = \"" + update.album + '"';
			query += ", length = \"" + update.length + '"';
			query += ",year = \"" + update.year + '"';
			query += ",lyrics = \"" + update.lyrics + '"';
			query += "WHERE song_id = " + std::to_string(update.song_id);

			std::cout << query << std::endl;
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


std::vector<Location> Dao::getAllFromLocations() {
	std::vector<Location> results;
	try
	{
		
		SQLite::Database db("microServiceDB.db");

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

std::vector<Songs> Dao::getAllFromSongs() {
	std::vector<Songs> results;
	try
	{

		SQLite::Database db("microServiceDB.db");

		SQLite::Statement query(db, "SELECT * FROM songs");

		while (query.executeStep()) {
			Songs add;
			add.song_id = query.getColumn("song_id");
			const char* name = query.getColumn("song_name");
			add.song_name = name;
			const char* artist = query.getColumn("artist");
			add.artist = artist;
			const char* album = query.getColumn("album");
			add.album = album;
			const char* length = query.getColumn("length");
			add.length = length;
			const char* year = query.getColumn("year");
			add.year = year;
			const char* lyrics = query.getColumn("lyrics");
			add.lyrics = lyrics;

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

		SQLite::Database db("microServiceDB.db");
		std::string searchValue = search.getSearchValue();
		if (searchValue != "")
		{
			std::cout << searchValue << std::endl;
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
std::vector<Songs> Dao::getByValue(Songs& search) {
	std::vector<Songs> results;
	try
	{

		SQLite::Database db("microServiceDB.db");
		std::string searchValue = search.getSearchValue();
		if (searchValue != "")
		{
			std::cout << searchValue << std::endl;
			SQLite::Statement query(db, "SELECT * FROM songs WHERE " + searchValue);


			while (query.executeStep()) {
				Songs add;
				add.song_id = query.getColumn(0);
				const char* name = query.getColumn(1);
				add.song_name = name;
				const char* artist = query.getColumn(2);
				add.artist = artist;
				const char* album = query.getColumn(3);
				add.album = album;
				const char* year = query.getColumn(3);
				add.year = year;
				const char* lyrics = query.getColumn(5);
				add.lyrics = lyrics;

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

		SQLite::Database db("microServiceDB.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
		SQLite::Transaction transaction(db);
		std::string query = "DELETE FROM Location WHERE " + searchValue;

		std::cout << query << std::endl;
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
bool Dao::deleteRow(Songs& deleteLocation) {
	bool success = true;
	try
	{
		std::string searchValue = deleteLocation.getSearchValue();

		if (searchValue != "")
		{

			SQLite::Database db("microServiceDB.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
			SQLite::Transaction transaction(db);
			std::string query = "DELETE FROM songs WHERE " + searchValue;

			std::cout << query << std::endl;
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