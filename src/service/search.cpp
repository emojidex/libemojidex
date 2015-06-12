#include "search.h"

using namespace std;

Emojidex::Service::Search::Search()
{
	this->current_page = 0;
}

Emojidex::Data::Collection Emojidex::Service::Search::term(string term)
{
	Emojidex::Data::Collection results;

	return results;
}
