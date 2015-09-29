#include "user.h"
#include "transactor.h"

Emojidex::Service::User::User()
{
	status = NONE;
	token = "";
	pro = false;
	premium = false;
}

Emojidex::Service::User::~User()
{
}

bool Emojidex::Service::User::authorize(string username, string token)
{
	Transactor transactor;
	//string response = transactor.get("users/authenticate", {{"auth_user", username}, {"auth_token", token}});
	
	// TODO WIP hack here
	status = VERIFIED;
	this->username = username;
	this->token = token;
	return true;
	
	//return false;
}

bool Emojidex::Service::User::login(string user, string password)
{
	return false;
}

bool Emojidex::Service::User::syncFavorites(bool detailed)
{
	Transactor transactor;

	string response = transactor.get("users/favorites", {{"auth_user", username}, 
			{"auth_token", token}, {"detailed", (detailed ? "true" : "false")}});

	favorites.mergeJSON(response);

	return true;
}

bool Emojidex::Service::User::addFavorite(string code)
{
	return false;
}

bool Emojidex::Service::User::removeFavorite(string code)
{
	return false;
}

bool Emojidex::Service::User::syncHistory(bool detailed)
{
	return false;
}

unsigned int Emojidex::Service::User::addHistory(string code)
{
	return 0;
}
