#include "user.h"
#include "transactor.h"
#include "rapidjson/document.h"

using namespace Emojidex::Data;
using namespace std;

Emojidex::Service::User::User()
{
	status = NONE;
	username = "";
	auth_token = "";
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
	string response = transactor.GET("users/authenticate", {{"username", username}, 
			{"token", token}});

	this->response = response;

	rapidjson::Document doc;
	doc.Parse(response.c_str());

	if (doc.HasParseError()) {
		this->status = FAILURE;
		this->username = username;
		this->auth_token = token;
		return false;
	}
	
	if (doc.IsObject() && doc.HasMember("auth_status")) {
		string ret_status = doc["auth_status"].GetString();
		if (ret_status.compare("verified") == 0) {
			this->status = VERIFIED;
			this->username = doc["auth_user"].GetString();
			this->auth_token = doc["auth_token"].GetString();
			this->pro = doc["pro"].GetBool();
			this->premium = doc["premium"].GetBool();
			return true;
		} else if (ret_status.compare("unverified") == 0) {
			this->status = UNVERIFIED;
			this->username = username;
			this->auth_token = token;
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

	string response = transactor.GET("users/favorites", {{"auth_user", username}, 
			{"auth_token", this->auth_token}, {"detailed", (detailed ? "true" : "false")}});

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

std::vector<Emojidex::Service::HistoryItem> Emojidex::Service::User::syncHistory(unsigned int page, unsigned int limit)
{
	if (page == 0)
		page = this->history_page + 1;

	std::vector<Emojidex::Service::HistoryItem> history_page;

	Emojidex::Service::Transactor transactor;
	std::string response = transactor.GET("users/history", {{"auth_token", this->auth_token}, 
			{"limit", std::to_string(limit)}, {"page", std::to_string(page)}});

	rapidjson::Document doc;
	doc.Parse(response.c_str());

	if (doc.HasParseError())
		return history_page;

	if (doc.IsObject()) {
		if (doc.HasMember("meta")) { //Check to see if a meta node is present
			this->history_total = doc["meta"]["total_count"].GetInt();
			this->history_page = doc["meta"]["page"].GetInt();
			for (rapidjson::SizeType i = 0; i < doc["history"].Size(); i++) {
				history_page.push_back(Emojidex::Service::HistoryItem(
							doc["history"][i]["emoji_code"].GetString(),
							doc["history"][i]["times_used"].GetInt(),
							doc["history"][i]["last_used"].GetString()));
			}
		} else if (doc.HasMember("status")) {
		// todo handle status
		}
	}

	mergeHistoryPage(history_page);
	sortHistory();

	return history_page;
}

void Emojidex::Service::User::mergeHistoryPage(std::vector<Emojidex::Service::HistoryItem> history_page)
{
	for (unsigned int i = 0; i < history_page.size(); i++) {
		mergeHistoryItem(history_page[i]);
	}
}

bool Emojidex::Service::User::mergeHistoryItem(Emojidex::Service::HistoryItem history_item)
{
	for (unsigned int i = 0; i < this->history.size(); i++) {
		if (history_item.emoji_code.compare(this->history[i].emoji_code) == 0) {
			this->history[i].times_used = history_item.times_used;
			this->history[i].last_used = history_item.last_used;
			return true;
		}
	}
	this->history.push_back(history_item);
	return false;
}

void Emojidex::Service::User::sortHistory()
{
	// TODO
}

bool Emojidex::Service::User::addHistory(string code)
{
	Emojidex::Service::Transactor transactor;
	std::string response = transactor.POST("users/history", {{"auth_token", this->auth_token}, 
			{"emoji_code", code}});

	this->response = response; // DEBUG

	rapidjson::Document doc;
	doc.Parse(response.c_str());

	if (doc.HasParseError())
		return false;

	if (doc.IsObject()) {
		if (doc.HasMember("emoji_code")) { // Make sure we're dealing with a history item
			std::string emoji_code = doc["emoji_code"].GetString();
			history.insert(history.begin(), Emojidex::Service::HistoryItem(
							emoji_code,
							doc["times_used"].GetInt(),
							doc["last_used"].GetString()));
			for (unsigned int i = 1; i < history.size(); i++) {
				if (history[i].emoji_code.compare(emoji_code) == 0) {
					history.erase(history.begin() + i, history.begin() + i + 1);
					break;
				}
			}
			return true;
		} else if (doc.HasMember("status")) {
			return false; // Status lines indicate an error, so just return false
		}
	}

	return false;
}
