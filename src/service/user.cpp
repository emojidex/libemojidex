#include "user.h"
#include "transactor.h"

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
	Transactor transactor;
	string response = transactor.get("users/authenticate", {{"username", username}, {"token", token}});
	
	return false;
}

unsigned char Emojidex::Service::User::authorized()
{
	if (status.compare("verified") == 0)
		return 1;

	return 0;
}

bool Emojidex::Service::User::login(string user, string password)
{
	return false;
}

bool Emojidex::Service::User::addFavorite(string code)
{
	return false;
}

bool Emojidex::Service::User::removeFavorite(string code)
{
	return false;
}

unsigned int Emojidex::Service::User::addHistory(string code)
{
	return 0;
}

bool Emojidex::Service::User::syncHistory()
{
	return false;
}
