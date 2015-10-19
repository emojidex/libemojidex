#include "indexes.h"
#include "transactor.h"

#include <boost/lexical_cast.hpp>
using namespace boost;
using namespace std;

Emojidex::Service::Indexes::Indexes()
{
	this->codes = new Emojidex::Data::MojiCodes();
}

Emojidex::Service::Indexes::~Indexes()
{
	delete this->codes;
}

void Emojidex::Service::Indexes::defaultLocale(string *object_locale, string *locale)
{
	if (locale->compare("") == 0) { // default arg
		if (object_locale->compare("") == 0) { // if not already defined 
			*locale = "en"; // default to english
		} else {
			*locale = *object_locale;
		}
	}
}

Emojidex::Data::MojiCodes Emojidex::Service::Indexes::mojiCodes(string locale)
{
	defaultLocale(&this->codes->locale, &locale);

	if (this->codes->locale.compare(locale) == 0)
		return *this->codes;

	Emojidex::Service::Transactor transactor;
	string response = transactor.get("moji_codes", {{"locale", locale}});
	
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

Emojidex::Data::Collection Emojidex::Service::Indexes::getStaticCollection(string name, 
		string locale, bool detailed)
{
	Emojidex::Data::Collection collect = Emojidex::Data::Collection();
	defaultLocale(&collect.locale, &locale);

	Emojidex::Service::Transactor transactor;
	string response = transactor.get(name, {{"locale", locale}, 
			{"detailed", TF(detailed)}});

	collect.mergeJSON(response);

	collect.locale = locale;

	return collect;
}

Emojidex::Data::Collection Emojidex::Service::Indexes::getDynamicCollection(string name, 
		unsigned int page, unsigned int limit, bool detailed)
{
	Emojidex::Data::Collection collect = Emojidex::Data::Collection();
	collect.detailed = detailed;
	collect.endpoint = name;

	Emojidex::Service::Transactor transactor;
	string response = transactor.get(name, {{"limit", lexical_cast<string>(limit)}, 
			{"page", lexical_cast<string>(page)}, {"detailed", TF(detailed)}});

	collect.mergeJSON(response);

	return collect;
}

Emojidex::Data::Collection Emojidex::Service::Indexes::utfEmoji(string locale, bool detailed)
{
	return getStaticCollection("utf_emoji", locale, detailed);
}

Emojidex::Data::Collection Emojidex::Service::Indexes::extendedEmoji(string locale, 
		bool detailed)
{
	return getStaticCollection("extended_emoji", locale, detailed);
}

Emojidex::Data::Collection Emojidex::Service::Indexes::nextPage(
		Emojidex::Data::Collection collection)
{
	return getDynamicCollection(collection.endpoint, collection.page + 1, collection.limit,
			collection.detailed);
}

Emojidex::Data::Collection Emojidex::Service::Indexes::emoji(unsigned int page, 
		unsigned int limit, bool detailed)
{
	Emojidex::Data::Collection collect = getDynamicCollection("emoji", page, limit, detailed);
	collect.setPagination(&Emojidex::Service::Indexes::nextPage, page, limit, detailed); 

	return collect;
}

Emojidex::Data::Collection Emojidex::Service::Indexes::newest(unsigned int page,
		unsigned int limit, bool detailed)
{
	Emojidex::Data::Collection collect = getDynamicCollection("newest", page, limit, detailed);
	collect.setPagination(&Emojidex::Service::Indexes::nextPage, page, limit, detailed); 

	return collect;
}

Emojidex::Data::Collection Emojidex::Service::Indexes::popular(unsigned int page,
		unsigned int limit, bool detailed)
{
	Emojidex::Data::Collection collect = getDynamicCollection("popular", page, limit, detailed);
	collect.setPagination(&Emojidex::Service::Indexes::nextPage, page, limit, detailed); 

	return collect;
}
