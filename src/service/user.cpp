#include "user.h"
#include "transactor.h"

Emojidex::Service::User::User()
{
	status = NONE;
	token = "";
}

Emojidex::Service::User::~User()
{
}

bool Emojidex::Service::User::authorize(string username, string token)
{
	Transactor transactor;
	string response = transactor.get("users/authenticate", {{"username", username}, {"token", token}});
	
	// TODO WIP hack here
	status = VERIFIED;
	username = username;
	token = token;
	return true;
	
	//return false;
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
