#include "indexes.h"
#include "transactor.h"
#include "collector.h"

using namespace std;
using namespace Emojidex::Data;

Emojidex::Service::Indexes::Indexes()
{
	this->codes = new Emojidex::Data::MojiCodes();
}

Emojidex::Service::Indexes::~Indexes()
{
	delete this->codes;
}

Emojidex::Data::MojiCodes Emojidex::Service::Indexes::mojiCodes(string locale)
{
	Emojidex::Service::Collector::defaultLocale(&this->codes->locale, &locale);

	if (this->codes->locale.compare(locale) == 0)
		return *this->codes;

	Emojidex::Service::Transactor transactor;
	string response = transactor.GET("moji_codes", {{"locale", locale}});
	
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
		unsigned int limit, bool detailed)
{
	return Emojidex::Service::Collector::getDynamicCollection("emoji", page, limit, detailed);
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
