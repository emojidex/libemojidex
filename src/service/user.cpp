#include "user.h"
#include "transactor.h"
#include "rapidjson/document.h"

using namespace Emojidex::Data;
using namespace std;

Emojidex::Service::User::User()
{
	status = NONE;
	username = "";
	token = "";
	pro = false;
	premium = false;
	r18 = false;
}

Emojidex::Service::User::~User()
{
}

bool Emojidex::Service::User::authorize(string username, string token)
{
	Transactor transactor;
	string response = transactor.get("users/authenticate", {{"username", username}, 
			{"token", token}});

	this->response = response;

	rapidjson::Document doc;
	doc.Parse(response.c_str());

	if (doc.HasParseError()) {
		this->status = FAILURE;
		this->username = username;
		this->token = token;
		return false;
	}
	
	if (doc.IsObject() && doc.HasMember("auth_status")) {
		string ret_status = doc["auth_status"].GetString();
		if (ret_status.compare("verified") == 0) {
			this->status = VERIFIED;
			this->username = doc["auth_user"].GetString();
			this->token = doc["auth_token"].GetString();
			this->pro = doc["pro"].GetBool();
			this->premium = doc["premium"].GetBool();
			return true;
		} else if (ret_status.compare("unverified") == 0) {
			this->status = UNVERIFIED;
			this->username = username;
			this->token = token;
			return false;
		}
	}

	return false;
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

std::vector<Emojidex::Service::HistoryItem> Emojidex::Service::User::syncHistory(unsigned int limit, unsigned int page, bool detailed)
{
	if (page == 0)
		page = this->history_page +=1;

	std::vector<Emojidex::Service::HistoryItem> history_page;

	transactor = Emojidex::Service::Transactor.new();
	std::string response = transactor.get("users/history", {{"auth_token", this->auth_token}, {"limit", limit}, {"page", page}});

	rapidjson::Document doc;
	doc.Parse(response.c_str());

	if (doc.HasParseError())
		return this;

	if (doc.IsObject()) {
		if (doc.HasMember("meta")) { //Check to see if a meta node is present
		this->history_total = doc["meta"]["total_count"].GetInt();
		this->history_page = doc["meta"]["page"].getInt();
		// todo: fill/merge history
		} else if (doc.HasMember("status") {
		// todo handle status
		}
	}

	return this;


	return history_page;
}

unsigned int Emojidex::Service::User::addHistory(string code)
{
	return 0;
}
