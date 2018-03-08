#include "songs.h"

Songs::Songs() : song_id {-1}, song_name{""},artist{""},album{""},length{""},year{""},lyrics{""}
{

}

std::string Songs::getInsertValues()
{
	std::string helperValue;

	helperValue = std::to_string(song_id);
	helperValue += ",\"" + song_name + '"';
	helperValue += ",\"" + artist + '"';
	helperValue += ",\"" + album + '"';
	helperValue += ",\"" + length + '"';
	helperValue += ",\"" + year + '"';
	helperValue += ",\"" + lyrics + '"';
	return helperValue;
}
std::string Songs::getSearchValue() {
	std::string helperValue = "";
	if (song_id != -1)
	{
		helperValue += " song_id = " + std::to_string(song_id);
	}

	if (song_name != "" && song_name != " ")
	{
		if (helperValue != "")
		{
			helperValue += " AND ";
		}

		helperValue += " song_name = \"" + song_name + '"';

	}

	if (artist != "" && artist != " ")
	{
		if (helperValue != "")
		{
			helperValue += " AND ";
		}

		helperValue += " artist = \"" + artist + '"';

	}
	if (album != "" && album != " ")
	{
		if (helperValue != "")
		{
			helperValue += " AND ";
		}

		helperValue += " album = \"" + album + '"';

	}
	if (length != "" && length != " ")
	{
		if (helperValue != "")
		{
			helperValue += " AND ";
		}

		helperValue += " length = \"" + length + '"';

	}
	if (year != ""  && year != " ")
	{
		if (helperValue != "")
		{
			helperValue += " AND ";
		}

		helperValue += " year = \"" + year + '"';

	}
/*	if (lyrics != ""  && lyrics  != " ")
	{
		if (helperValue != "")
		{
			helperValue += " AND ";
		}

		helperValue += " lyrics = \"" + lyrics + '"';

	}
	*/

	return helperValue;
}
