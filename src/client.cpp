#include "client.h"
#include "client/search.h"

Emojidex::Client::Client()
{
	this->search = new Emojidex::SearchClient();
}

std::string Emojidex::Client::version()
{
	return EMOJIDEX_VERSION;
}
