#include "client.h"
#include "client/search.h"

Emojidex::Client::Client()
{
	this->search = new Emojidex::SearchClient();
}

char Emojidex::Client::apiVersion()
{
	return 1;
}
