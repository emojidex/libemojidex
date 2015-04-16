#include "collection.h"

Emojidex::Data::Collection::Collection()
{
  moreMethod = NULL;
  page = 0;
  limit = 0;
  total_count = 0;
}

Emojidex::Data::Collection::~Collection()
{
}

Emojidex::Data::Collection Emojidex::Data::Collection::merge(Emojidex::Data::Collection delta_collection)
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

void Emojidex::Data::Collection::setPagination(Emojidex::Data::Collection (*moreMethod)(Emojidex::Data::Collection), unsigned int starting_page, unsigned int limit)
{
}
