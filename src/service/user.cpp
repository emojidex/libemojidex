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

Emojidex::Data::Collection Emojidex::Service::User::syncHistory(unsigned int page, unsigned int limit, bool detailed)
{
	Emojidex::Data::Collection collect = Emojidex::Data::Collection();
	collect.detailed = detailed;
	collect.endpoint = "users/history";
	//collect.setPagination(&Emojidex::Service::User::syncHistory, page + 1, limit, detailed); 

	Emojidex::Service::Transactor transactor;
	//string response = transactor.get("users/history", {{"limit", lexical_cast<string>(limit)}, 
	//		{"page", lexical_cast<string>(page)}, {"detailed", TF(detailed)}});

	//collect.mergeJSON(response);

	return collect;
}

unsigned int Emojidex::Service::User::addHistory(string code)
{
	return 0;
}
