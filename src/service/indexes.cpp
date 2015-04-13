#include "indexes.h"
#include "transactor.h"
#include "rapidjson/document.h"

Emojidex::Service::Indexes::Indexes()
{
	this->codes = new Emojidex::Data::MojiCodes();
}

Emojidex::Service::Indexes::~Indexes()
{
	delete this->codes;
}

void defaultLocale(string *object_locale, string *locale)
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

Emojidex::Data::Collection getStaticCollection(string name, string locale)
{
  Emojidex::Data::Collection collect = Emojidex::Data::Collection();
  defaultLocale(&collect.locale, &locale);

	Emojidex::Service::Transactor transactor;
	string response = transactor.get(name, {{"locale", locale}});

	rapidjson::Document d;
	d.Parse(response.c_str());

	if (d.HasParseError())
    return collect; // return empty collection


 /* rapidjson::Value& arr = d[0];
	for (rapidjson::Value::ConstMemberIterator item = arr.MemberBegin();
			item != arr.MemberEnd(); item++) {
    Emojidex::Data::Emoji moji = Emojidex::Data::Emoji();
    //moji.code = item["moji"].getString();
    cout << "CODE: " << item["moji"].getString() << endl;
		//collect.emoji[item->code.GetString()] = item->value.GetString();
  }*/

  collect.locale = locale;

  return collect;
}

Emojidex::Data::Collection Emojidex::Service::Indexes::utfEmoji(string locale)
{
  return getStaticCollection("utf_emoji", locale);
}

Emojidex::Data::Collection Emojidex::Service::Indexes::extendedEmoji(string locale)
{
  return getStaticCollection("extended_emoji", locale);
}
