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

Emojidex::Data::Collection getStaticCollection(string name, string locale, bool detailed)
{
  Emojidex::Data::Collection collect = Emojidex::Data::Collection();
  defaultLocale(&collect.locale, &locale);

	Emojidex::Service::Transactor transactor;
	string response = transactor.get(name, {{"locale", locale}});

	rapidjson::Document d;
	d.Parse(response.c_str());

	if (d.HasParseError())
    return collect; // return empty collection

  for (rapidjson::SizeType i = 0; i < d.Size(); i++) {
    Emojidex::Data::Emoji moji = Emojidex::Data::Emoji();
    moji.code = d[i]["code"].GetString();
    if (d[i]["moji"].IsString()) { moji.moji = d[i]["moji"].GetString(); }
    if (d[i]["unicode"].IsString()) { moji.unicode = d[i]["unicode"].GetString(); }
    d[i]["category"].IsString()? moji.category = d[i]["category"].GetString() : moji.category = "";

    rapidjson::Value& tags = d[i]["tags"];
    assert(tags.IsArray());
    for (rapidjson::SizeType tag_i = 0; tag_i < tags.Size(); tag_i++)
      moji.tags.push_back(tags[tag_i].GetString());

    collect.emoji[moji.code] = moji;
  }

  collect.locale = locale;

  return collect;
}

Emojidex::Data::Collection Emojidex::Service::Indexes::utfEmoji(string locale, bool detailed)
{
  return getStaticCollection("utf_emoji", locale, detailed);
}

Emojidex::Data::Collection Emojidex::Service::Indexes::extendedEmoji(string locale, bool detailed)
{
  return getStaticCollection("extended_emoji", locale, detailed);
}
