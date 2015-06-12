#include "indexes.h"
#include "transactor.h"

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

void Emojidex::Service::Indexes::fillEmojiFromJSON(Emojidex::Data::Collection* collect, 
		rapidjson::Value& d)
{
	for (rapidjson::SizeType i = 0; i < d.Size(); i++) {
		Emojidex::Data::Emoji moji = Emojidex::Data::Emoji();
		moji.code = d[i]["code"].GetString();
		if (d[i]["moji"].IsString()) { moji.moji = d[i]["moji"].GetString(); }
		if (d[i]["unicode"].IsString()) { moji.unicode = d[i]["unicode"].GetString(); }
		d[i]["category"].IsString()? 
			moji.category = d[i]["category"].GetString() : moji.category = "";
		if(d[i].HasMember("checksums"))
		{
			const rapidjson::Value& checksums = d[i]["checksums"];
			const rapidjson::Value& svg = checksums["svg"];
			const rapidjson::Value& png = checksums["png"];
			if(svg.IsString())	moji.checksums.svg = svg.GetString();
			for(rapidjson::Value::ConstMemberIterator it = png.MemberBegin();  it != png.MemberEnd();  ++it)
				if(it->value.IsString())	moji.checksums.png[it->name.GetString()] = it->value.GetString();
		}

		rapidjson::Value& tags = d[i]["tags"];
		assert(tags.IsArray());
		for (rapidjson::SizeType tag_i = 0; tag_i < tags.Size(); tag_i++)
			moji.tags.push_back(tags[tag_i].GetString());

		collect->emoji[moji.code] = moji;
	}
}

void Emojidex::Service::Indexes::fillMetaFromJSON(Emojidex::Data::Collection* collect, 
		rapidjson::Value& d)
{
	collect->total_count = d["total_count"].GetInt();
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

	rapidjson::Document d;
	d.Parse(response.c_str());

	if (d.HasParseError())
		return collect; // return empty collection

	fillEmojiFromJSON(&collect, d);

	collect.locale = locale;

	return collect;
}

Emojidex::Data::Collection Emojidex::Service::Indexes::getDynamicCollection(string name, 
		unsigned int limit, unsigned int page, bool detailed)
{
	Emojidex::Data::Collection collect = Emojidex::Data::Collection();
	collect.detailed = detailed;
	collect.endpoint = name;

	Emojidex::Service::Transactor transactor;
	string response = transactor.get(name, {{"limit", to_string(limit)}, 
			{"page", to_string(page)}, {"detailed", TF(detailed)}});

	rapidjson::Document d;
	d.Parse(response.c_str());

	if (d.HasParseError())
		return collect; // return empty collection

	fillEmojiFromJSON(&collect, d["emoji"]);
	fillMetaFromJSON(&collect, d["meta"]);

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
	return getDynamicCollection(collection.endpoint, collection.limit, collection.page + 1, 
			collection.detailed);
}

Emojidex::Data::Collection Emojidex::Service::Indexes::emoji(unsigned int limit, 
		unsigned int page, bool detailed)
{
	Emojidex::Data::Collection collect = getDynamicCollection("emoji", limit, page, detailed);
	collect.setPagination(&Emojidex::Service::Indexes::nextPage, page, limit); 

	return collect;
}

Emojidex::Data::Collection Emojidex::Service::Indexes::newest(unsigned int limit, 
		unsigned int page, bool detailed)
{
	Emojidex::Data::Collection collect = getDynamicCollection("newest", limit, page, detailed);
	collect.setPagination(&Emojidex::Service::Indexes::nextPage, page, limit); 

	return collect;
}

Emojidex::Data::Collection Emojidex::Service::Indexes::popular(unsigned int limit, 
		unsigned int page, bool detailed)
{
	Emojidex::Data::Collection collect = getDynamicCollection("popular", limit, page, detailed);
	collect.setPagination(&Emojidex::Service::Indexes::nextPage, page, limit); 

	return collect;
}
