#include "collection.h"

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

	for (auto em : emoji)
	{
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

Emojidex::Data::Collection Emojidex::Data::Collection::merge(
		Emojidex::Data::Collection delta_collection)
{
	for (auto new_moji : delta_collection.emoji)
		this->emoji[new_moji.first] = new_moji.second;

	return *this;
}

Emojidex::Data::Collection Emojidex::Data::Collection::operator<<(Emojidex::Data::Collection delta_collection)
{
	return this->merge(delta_collection);
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
		unsigned int starting_page, unsigned int limit)
{
}
