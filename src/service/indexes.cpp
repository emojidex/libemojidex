#include "indexes.h"
#include "transactor.h"
#include "collector.h"

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
	
	rapidjson::Document d;
	d.Parse(response.c_str());

	if (d.HasParseError())
		return *this->codes;

	rapidjson::Value& ms = d["moji_string"];
	this->codes->moji_string = ms.GetString();
	
	const rapidjson::Value& ma = d["moji_array"];
	for (rapidjson::SizeType i = 0; i < ma.Size(); i++)
		this->codes->moji_array.push_back(ma[i].GetString());

	const rapidjson::Value& mi = d["moji_index"];
	for (rapidjson::Value::ConstMemberIterator item = mi.MemberBegin();
			item != mi.MemberEnd(); item++)
		this->codes->moji_index[item->name.GetString()] = item->value.GetString();

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
	return Emojidex::Service::Collector::getAuthorizedDynamicCollection("newest", auth_token, page, limit, detailed);
}

Emojidex::Data::Collection Emojidex::Service::Indexes::popular(std::string auth_token, unsigned int page,
		unsigned int limit, bool detailed)
{
	return Emojidex::Service::Collector::getAuthorizedDynamicCollection("popular", auth_token, page, limit, detailed);
}

Emojidex::Data::Collection Emojidex::Service::Indexes::userEmoji(std::string username, unsigned int page, 
		unsigned int limit, bool detailed)
{
	std::stringstream path;
	path << "users/" << username << "/emoji";
	return Emojidex::Service::Collector::getDynamicCollection(path.str(), page, limit, detailed);
}
