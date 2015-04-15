#include "collection.h"

Emojidex::Data::Collection Emojidex::Data::Collection::more()
{
  return false;
}

void Emojidex::Data::Collection::setPagination(Emojidex::Data::Collection (*moreMethod)(Emojidex::Data::Collection, unsigned int), unsigned int starting_page, unsigned int limit)
{
}
