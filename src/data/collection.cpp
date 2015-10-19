#include "collection.h"

#include "rapidjson/document.h"

using namespace std;

Emojidex::Data::Collection::Collection()
{
	moreMethod = NULL;
	page = 0;
	limit = 0;
	total_count = 0;
	endpoint = "";
}

Emojidex::Data::Collection::~Collection()
{
}

vector<Emojidex::Data::Emoji> Emojidex::Data::Collection::all()
{
	vector<Emojidex::Data::Emoji> eav;

	for (auto em : emoji) {
		eav.push_back(em.second);
	}

	return eav;
}

Emojidex::Data::Emoji Emojidex::Data::Collection::add(Emojidex::Data::Emoji new_emoji)
{
	return emoji[new_emoji.code] = new_emoji;
}

Emojidex::Data::Emoji Emojidex::Data::Collection::findByMoji(string moji)
{
	for (auto em : emoji)
		if (em.second.moji.compare(moji) == 0)
			return em.second;
	return Emojidex::Data::Emoji();
}

Emojidex::Data::Emoji Emojidex::Data::Collection::findByCode(string code)
{
	return emoji[code];
}

Emojidex::Data::Emoji Emojidex::Data::Collection::findByUnicode(string unicode)
{
	for (auto em : emoji)
		if (em.second.unicode.compare(unicode) == 0)
			return em.second;
	return Emojidex::Data::Emoji();
}

Emojidex::Data::Collection Emojidex::Data::Collection::category(string category)
{
	Emojidex::Data::Collection collect;

	for (auto em : emoji)
		if (em.second.category.compare(category) == 0)
			collect.emoji[em.second.code] = em.second;

	return collect;
}

Emojidex::Data::Collection* Emojidex::Data::Collection::merge(
		Emojidex::Data::Collection delta_collection)
{
	for (auto new_moji : delta_collection.emoji)
		this->emoji[new_moji.first] = new_moji.second;

	this->page = delta_collection.page;

	return this;
}

Emojidex::Data::Collection* Emojidex::Data::Collection::operator<<(Emojidex::Data::Collection delta_collection)
{
	return this->merge(delta_collection);
}


void Emojidex::Data::Collection::fillEmojiFromJSON(rapidjson::Value& d)
{
	Emojidex::Data::Collection collect;

	for (rapidjson::SizeType i = 0; i < d.Size(); i++) {
		Emojidex::Data::Emoji moji = Emojidex::Data::Emoji();
		moji.code = d[i]["code"].GetString();
		if (d[i]["moji"].IsString()) { moji.moji = d[i]["moji"].GetString(); }
		if (d[i]["unicode"].IsString()) { moji.unicode = d[i]["unicode"].GetString(); }
		d[i]["category"].IsString()? 
			moji.category = d[i]["category"].GetString() : moji.category = "";
		if (d[i].HasMember("checksums"))
		{
			const rapidjson::Value& checksums = d[i]["checksums"];
			
			if (checksums.HasMember("svg")) {
				const rapidjson::Value& svg = checksums["svg"];
				if(svg.IsString())	moji.checksums.svg = svg.GetString();
			}

			if (checksums.HasMember("png")) {
				const rapidjson::Value& png = checksums["png"];
				for(rapidjson::Value::ConstMemberIterator it = png.MemberBegin();  it != png.MemberEnd();  ++it)
					if(it->value.IsString())	moji.checksums.png[it->name.GetString()] = it->value.GetString();
			}
		}

		rapidjson::Value& tags = d[i]["tags"];
		assert(tags.IsArray());
		for (rapidjson::SizeType tag_i = 0; tag_i < tags.Size(); tag_i++)
			moji.tags.push_back(tags[tag_i].GetString());

		rapidjson::Value& variants = d[i]["variants"];
		assert(variants.IsArray());
		for (rapidjson::SizeType variant_i = 0; variant_i < variants.Size(); variant_i++)
			moji.variants.push_back(variants[variant_i].GetString());

		collect.emoji[moji.code] = moji;
	}

	this->merge(collect);
}

Emojidex::Data::Collection* Emojidex::Data::Collection::mergeJSON(string json_string)
{
	rapidjson::Document doc;
	doc.Parse(json_string.c_str());

	if (doc.HasParseError())
		return this;

	if (doc.IsObject() && doc.HasMember("meta")) { //Check to see if a meta node is present
		this->total_count = doc["meta"]["total_count"].GetInt();
		fillEmojiFromJSON(doc["emoji"]);
	} else {
		assert(doc.IsArray());
		fillEmojiFromJSON(doc);
	}

	return this;
}

Emojidex::Data::Collection Emojidex::Data::Collection::more()
{
	if (moreMethod == NULL)
		return Emojidex::Data::Collection();

	Emojidex::Data::Collection collect = this->moreMethod(*this);

	this->merge(collect);

	return collect;
}

void Emojidex::Data::Collection::setPagination(
		Emojidex::Data::Collection (*moreMethod)(Emojidex::Data::Collection), 
		unsigned int limit, unsigned int starting_page, bool detailed)
{
	this->moreMethod = moreMethod;
	this->page = starting_page;
	this->limit = limit;
}
