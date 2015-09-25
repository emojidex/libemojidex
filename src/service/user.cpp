#include "user.h"

Emojidex::Service::User::User()
{
	status = "none";
	token = "";
}

Emojidex::Service::User::~User()
{
}

bool Emojidex::Service::User::authorize(string username, string token)
{
	return false;
}

unsigned char Emojidex::Service::User::authorized()
{
	if (status.compare("verified") == 0)
		return 1;

	return 0;
}

bool addFavorite(string code)
{
	return false;
}

bool removeFavorite(string code)
{
	return false;
}

unsigned int addHistory(string code)
{
	return 0;
}

bool syncHistory()
{
	return false;
}
