#include "client.h"
#include "client/transactor.h"
#include "client/search.h"

Emojidex::Client::Client()
{
	this->Search = new Emojidex::SearchClient();
	//this->transactor = new Emojidex::Transactor();
}

char Emojidex::Client::apiVersion()
{
	return 1;
}
