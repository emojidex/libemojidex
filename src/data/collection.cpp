#include "collection.h"

#include "../service/collector.h"

using namespace std;
using namespace Emojidex::Service;

Emojidex::Data::Collection::Collection()
{
	moreMethod = NULL;
	total_count = 0;
	endpoint = "";
	opts.setCollectionDefaults();
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

bool Emojidex::Data::Collection::remove(std::string code)
{
	if (emoji.erase(code) == 1)
		return true;

	return false;
}

Emojidex::Data::Emoji Emojidex::Data::Collection::findByMoji(std::string moji)
{
	for (auto em : emoji)
		if (em.second.moji.compare(moji) == 0)
			return em.second;
	return Emojidex::Data::Emoji();
}

Emojidex::Data::Emoji Emojidex::Data::Collection::findByCode(std::string code)
{
	//TODO unescape code
	//TODO avoid auto insert
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

	this->opts.page(delta_collection.opts.getPage());

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
		moji.fillFromJSON(d[i]);
		if (moji.code.compare("") != 0)
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

//void Emojidex::Data::Collection::parseQueryOpts(Emojidex::Service::QueryOpts opts)
//{
//	username = opts.getValue("username");
//	auth_token = opts.getValue("auth_token");
//	page = opts.getPage();
//	limit = opts.getLimit();
//	tags = opts.tags;
//	categories = opts.categories;
//	ext_opts = opts.ext_opts;
//	detailed = opts.getDetailed();
//}

Emojidex::Data::Collection Emojidex::Data::Collection::genericMore()
{
	if (endpoint.compare("") == 0)
		return *this;
	
	this->opts.page(this->opts.getPage() + 1);
	Collection collect = Collector::getCollection(*this);
	this->merge(collect);

	return *this;
}

Emojidex::Data::Collection Emojidex::Data::Collection::more()
{
	if (moreMethod == NULL)
		return this->genericMore();

	Emojidex::Data::Collection collect = this->moreMethod(*this);

	this->merge(collect);

	return collect;
}

void Emojidex::Data::Collection::setPagination(
		Emojidex::Data::Collection (*moreMethod)(Emojidex::Data::Collection), 
		unsigned int starting_page, unsigned int limit, bool detailed)
{
	this->moreMethod = moreMethod;
	this->opts.page(starting_page);
	this->opts.limit(limit);
}
