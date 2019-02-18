#include "indexes.h"
#include "transactor.h"
#include "collector.h"

#include <msgpack.hpp>

using namespace std;
using namespace Emojidex::Data;

namespace
{
  bool is_logged_in(const Emojidex::Service::User *user)
  {
  	return user != NULL && !user->auth_token.empty();
  }
}

Emojidex::Service::Indexes::Indexes()
	: user(NULL)
{
	this->codes = new Emojidex::Data::MojiCodes();
}

void Emojidex::Service::Indexes::setUser(const Emojidex::Service::User *user)
{
	this->user = user;
}

Emojidex::Service::Indexes::~Indexes()
{
	delete this->codes;
}

Emojidex::Data::MojiCodes Emojidex::Service::Indexes::mojiCodes(string locale)
{
	Emojidex::Service::Transactor transactor;
	string response = is_logged_in(user) ?
		transactor.GET("moji_codes", {{"locale", locale}, {"auth_token", user->auth_token}}) :
		transactor.GET("moji_codes", {{"locale", locale}});

	msgpack::object_handle oh = msgpack::unpack(response.data(), response.size());
	msgpack::object root = oh.get();

	if(root.type == msgpack::type::MAP)
	{
		auto m = root.as<std::map<std::string, msgpack::object>>();

		if(m.count("moji_string") != 0)
		{
			const msgpack::object ms = m.at("moji_string");
			if(ms.type == msgpack::type::STR)
				this->codes->moji_string = ms.as<std::string>();
		}

		if(m.count("moji_array") != 0)
		{
			const msgpack::object ma = m.at("moji_array");
			if(ma.type == msgpack::type::ARRAY)
			{
				for(unsigned int i = 0;  i < ma.via.array.size;  ++i)
				{
					auto value = ma.via.array.ptr[i];
					if(value.type == msgpack::type::STR)
					 this->codes->moji_array.push_back(value.as<std::string>());
				}
			}
		}

		if(m.count("moji_index") != 0)
		{
			const msgpack::object mi = m.at("moji_index");
			if(mi.type == msgpack::type::MAP)
			{
				for(unsigned int i = 0;  i < mi.via.map.size;  ++i)
				{
					auto pair = mi.via.map.ptr[i];
					if(pair.key.type == msgpack::type::STR && pair.val.type == msgpack::type::STR)
						this->codes->moji_index[pair.key.as<std::string>()] = pair.val.as<std::string>();
				}
			}
		}
	}

	this->codes->locale = locale;

	return *this->codes;
}

Emojidex::Data::Collection Emojidex::Service::Indexes::utfEmoji(string locale, bool detailed)
{
	return Emojidex::Service::Collector::getStaticCollection("utf_emoji", locale, detailed);
}

Emojidex::Data::Collection Emojidex::Service::Indexes::extendedEmoji(string locale, 
		bool detailed)
{
	return Emojidex::Service::Collector::getStaticCollection("extended_emoji", locale, detailed);
}

Emojidex::Data::Collection Emojidex::Service::Indexes::emoji(unsigned int page, 
		unsigned int limit, bool detailed, Emojidex::Service::QueryOpts *conditions)
{
	Emojidex::Service::QueryOpts tmp;
	if(is_logged_in(user))
	{
		if(conditions == NULL)
			conditions = &tmp;
		if(conditions->getAuthToken().empty())
			conditions->auth_token(user->auth_token);
	}
	return Emojidex::Service::Collector::getDynamicCollection("emoji", page, limit, detailed, conditions);
}

Emojidex::Data::Collection Emojidex::Service::Indexes::newest(std::string auth_token, unsigned int page,
		unsigned int limit, bool detailed)
{
	if (auth_token.empty() && is_logged_in(user))
		auth_token = user->auth_token;
	return Emojidex::Service::Collector::getAuthorizedDynamicCollection("newest", auth_token, page, limit, detailed);
}

Emojidex::Data::Collection Emojidex::Service::Indexes::popular(std::string auth_token, unsigned int page,
		unsigned int limit, bool detailed)
{
	if (auth_token.empty() && is_logged_in(user))
		auth_token = user->auth_token;
	return Emojidex::Service::Collector::getAuthorizedDynamicCollection("popular", auth_token, page, limit, detailed);
}

Emojidex::Data::Collection Emojidex::Service::Indexes::userEmoji(std::string username, unsigned int page, 
		unsigned int limit, bool detailed)
{
	std::stringstream path;
	path << "users/" << username << "/emoji";
	if(is_logged_in(user))
	{
		Emojidex::Service::QueryOpts opts;
		opts.auth_token(user->auth_token);
		return Emojidex::Service::Collector::getDynamicCollection(path.str(), page, limit, detailed, &opts);
	}
	return Emojidex::Service::Collector::getDynamicCollection(path.str(), page, limit, detailed);
}
