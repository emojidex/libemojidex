#include "../libemojidex.h"
#include "user.h"
#include "transactor.h"
#include "indexes.h"
#include "msgpack.hpp"

using namespace Emojidex::Data;
using namespace std;

#define MSGPACK_OBJ2TYPE(dest, src, key, msgpack_type, result_type) { if(src.count(key) != 0) { const msgpack::object target = src.at(key); if(target.type == msgpack_type) dest = target.as<result_type>(); } }
#define MSGPACK_OBJ2STR(dest, src, key) MSGPACK_OBJ2TYPE(dest, src, key, msgpack::type::STR, std::string)
#define MSGPACK_OBJ2INT(dest, src, key) MSGPACK_OBJ2TYPE(dest, src, key, msgpack::type::POSITIVE_INTEGER, int)
#define MSGPACK_OBJ2BOOLEAN(dest, src,key) MSGPACK_OBJ2TYPE(dest, src, key, msgpack::type::BOOLEAN, bool)

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

	const msgpack::object_handle oh = msgpack::unpack(response.data(), response.size());
	const msgpack::object root = oh.get();

	if(root.type != msgpack::type::MAP)
	{
		this->status = FAILURE;
		this->username = username;
		this->auth_token = token;
		return false;
	}

	const auto m = root.as<std::map<std::string, msgpack::object>>();

	std::string ret_status;
	MSGPACK_OBJ2STR(ret_status, m, "auth_status");

	if(ret_status.compare("verified") == 0)
	{
		this->status = VERIFIED;
		MSGPACK_OBJ2STR(this->username, m, "auth_user");
		MSGPACK_OBJ2STR(this->auth_token, m, "auth_token");
		MSGPACK_OBJ2BOOLEAN(this->pro, m, "pro");
		MSGPACK_OBJ2BOOLEAN(this->premium, m, "premium");
		MSGPACK_OBJ2BOOLEAN(this->r18, m, "r18");
		return true;
	}

	if(ret_status.compare("unverified") == 0)
	{
		this->status = UNVERIFIED;
		this->username = username;
		this->auth_token = token;
		return false;
	}

	this->status = FAILURE;
	this->username = username;
	this->auth_token = token;
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

	favorites.mergeMsgPack(response);

	return true;
}

bool Emojidex::Service::User::addFavorite(string code)
{
	Transactor transactor;

	string response = transactor.POST("users/favorites", {{"auth_user", username},
			{"auth_token", this->auth_token}, {"emoji_code", Emojidex::escapeCode(code)}});

	const msgpack::object_handle oh = msgpack::unpack(response.data(), response.size());
	const msgpack::object root = oh.get();

	if(root.type != msgpack::type::MAP)
		return false;

	const auto m = root.as<std::map<std::string, msgpack::object>>();

	if(m.count("code") != 0)	//Check to see if a code is actually present
	{
		Emojidex::Data::Emoji em;
		em.fillFromMsgPack(root);
		this->favorites.add(em);
		return true;
	}

	return false;
}

bool Emojidex::Service::User::removeFavorite(string code)
{
	Transactor transactor;

	string response = transactor.DELETE("users/favorites", {{"auth_user", username},
			{"auth_token", this->auth_token}, {"emoji_code", Emojidex::escapeCode(code)}});

	const msgpack::object_handle oh = msgpack::unpack(response.data(), response.size());
	const msgpack::object root = oh.get();

	if(root.type != msgpack::type::MAP)
		return false;

	const auto m = root.as<std::map<std::string, msgpack::object>>();

	if(m.count("code") != 0)	//Check to see if a code is actually present
	{
		std::string code;
		MSGPACK_OBJ2STR(code, m, "code");
		this->favorites.remove(code);
		return true;
	}

	return false;
}

std::vector<Emojidex::Service::HistoryItem> Emojidex::Service::User::syncHistory(unsigned int page, unsigned int limit)
{
	if (page == 0)
		page = this->history_page + 1;

	std::vector<Emojidex::Service::HistoryItem> new_history_page;

	Emojidex::Service::Transactor transactor;
	std::string response = transactor.GET("users/history", {{"auth_token", this->auth_token}, 
			{"limit", std::to_string(limit)}, {"page", std::to_string(page)}});

	const msgpack::object_handle oh = msgpack::unpack(response.data(), response.size());
	const msgpack::object root = oh.get();

	if(root.type != msgpack::type::MAP)
		return new_history_page;

	const auto m = root.as<std::map<std::string, msgpack::object>>();

	if(m.count("meta") != 0)	//Check to see if a meta node is present
	{
		const msgpack::object meta_object = m.at("meta");
		if(meta_object.type == msgpack::type::MAP)
		{
			const auto meta = meta_object.as<std::map<std::string, msgpack::object>>();
			MSGPACK_OBJ2INT(this->history_total, meta, "total_count");
			MSGPACK_OBJ2INT(this->history_page, meta, "page");
		}

		if(m.count("history") != 0)
		{
			const msgpack::object history_object = m.at("history");

			if(history_object.type == msgpack::type::ARRAY)
			{
				for(size_t i = 0;  i < history_object.via.array.size;  ++i)
				{
					if(history_object.via.array.ptr[i].type == msgpack::type::MAP)
					{
						auto history = history_object.via.array.ptr[i].as<std::map<std::string, msgpack::object>>();
						std::string emoji_code;
						int times_used;
						std::string last_used;

						MSGPACK_OBJ2STR(emoji_code, history, "emoji_code");
						MSGPACK_OBJ2INT(times_used, history, "times_used");
						MSGPACK_OBJ2STR(last_used, history, "last_used");

						new_history_page.push_back(
							Emojidex::Service::HistoryItem(emoji_code, times_used, last_used)
						);
					}
				}
			}
		}
	}

	mergeHistoryPage(new_history_page);
	sortHistory();

	return new_history_page;
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

bool historyComparitor(Emojidex::Service::HistoryItem const& lhs, Emojidex::Service::HistoryItem const& rhs)
{
	if (lhs.last_used_posix > rhs.last_used_posix)
		return true;
	return false;
}

void Emojidex::Service::User::sortHistory()
{
	std::sort(this->history.begin(), this->history.end(), &historyComparitor);
}

bool Emojidex::Service::User::addHistory(string code)
{
	Emojidex::Service::Transactor transactor;
	std::string response = transactor.POST("users/history", {{"auth_token", this->auth_token}, 
			{"emoji_code", Emojidex::escapeCode(code)}});

	const msgpack::object_handle oh = msgpack::unpack(response.data(), response.size());
	const msgpack::object root = oh.get();

	if(root.type != msgpack::type::MAP)
		return false;

	const auto m = root.as<std::map<std::string, msgpack::object>>();

	if(m.count("emoji_code") != 0)	// Make sure we're dealing with a history item
	{
		std::string emoji_code;
		int times_used;
		std::string last_used;
		MSGPACK_OBJ2STR(emoji_code, m, "emoji_code");
		MSGPACK_OBJ2INT(times_used, m, "times_used");
		MSGPACK_OBJ2STR(last_used, m, "last_used");

		for(auto it = history.begin();  it != history.end();  ++it)
		{
			if(it->emoji_code.compare(emoji_code) == 0)
			{
				history.erase(it);
				break;
			}
		}

		history.insert(
			history.begin(),
			Emojidex::Service::HistoryItem(emoji_code, times_used, last_used)
		);
		return true;
	}

	return false;
}


bool Emojidex::Service::User::syncMyEmoji()
{
	if (this->username.empty())
		return false;

	Emojidex::Service::Indexes idx;
	this->my_emoji = idx.userEmoji(this->username);
	return true;
}

bool Emojidex::Service::User::syncFollowing()
{
	Transactor transactor;

	string response = transactor.GET("users/following", {{"auth_user", username}, 
			{"auth_token", this->auth_token}});

	const msgpack::object_handle oh = msgpack::unpack(response.data(), response.size());
	const msgpack::object root = oh.get();

	if(root.type != msgpack::type::MAP)
		return false;

	this->following.clear();
	const auto m = root.as<std::map<std::string, msgpack::object>>();

	if(m.count("following") != 0)
	{
		const msgpack::object following_object = m.at("following");
		if(following_object.type == msgpack::type::ARRAY)
		{
			for(size_t i = 0;  i < following_object.via.array.size;  ++i)
			{
				const msgpack::object& user = following_object.via.array.ptr[i];
				if(user.type == msgpack::type::STR)
					this->following.push_back(user.as<std::string>());
			}
		}
		return true;
	}

	return false;
}

bool Emojidex::Service::User::addFollowing(string username)
{
	Transactor transactor;

	string response = transactor.POST("users/following", {{"auth_user", username},
			{"auth_token", this->auth_token}, {"username", username}});

	const msgpack::object_handle oh = msgpack::unpack(response.data(), response.size());
	const msgpack::object root = oh.get();

	if(root.type != msgpack::type::MAP)
		return false;

	const auto m = root.as<std::map<std::string, msgpack::object>>();

	if(m.count("username") != 0)	//Check to see if a code is actually present
	{
		std::string name;
		MSGPACK_OBJ2STR(name, m, "username");
		this->following.push_back(name);
		return true;
	}

	return false;
}

bool Emojidex::Service::User::removeFollowing(string username)
{
	Transactor transactor;

	string response = transactor.DELETE("users/following", {{"auth_user", username},
			{"auth_token", this->auth_token}, {"username", username}});

	const msgpack::object_handle oh = msgpack::unpack(response.data(), response.size());
	const msgpack::object root = oh.get();

	if(root.type != msgpack::type::MAP)
		return false;

	const auto m = root.as<std::map<std::string, msgpack::object>>();

	if(m.count("username") != 0)	//Check to see if a code is actually present
	{
		std::string name;
		MSGPACK_OBJ2STR(name, m, "username");

		if(username.compare(name) != 0)
			return false;

		const auto it = std::find(this->following.begin(), this->following.end(), username);
		if(it == this->following.end())
			return false;

		this->following.erase(it);

		return true;
	}

	return false;
}

bool Emojidex::Service::User::syncFollowers()
{
	Transactor transactor;

	string response = transactor.GET("users/followers", {{"auth_user", username}, 
			{"auth_token", this->auth_token}});

	const msgpack::object_handle oh = msgpack::unpack(response.data(), response.size());
	const msgpack::object root = oh.get();

	if(root.type != msgpack::type::MAP)
		return false;

	this->followers.clear();
	const auto m = root.as<std::map<std::string, msgpack::object>>();

	if(m.count("followers") != 0)
	{
		const msgpack::object following_object = m.at("followers");
		if(following_object.type == msgpack::type::ARRAY)
		{
			for(size_t i = 0;  i < following_object.via.array.size;  ++i)
			{
				const msgpack::object& user = following_object.via.array.ptr[i];
				if(user.type == msgpack::type::STR)
					this->followers.push_back(user.as<std::string>());
			}
		}
		return true;
	}

	return false;
}
