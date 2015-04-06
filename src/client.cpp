#include "client.h"

Emojidex::Client::Client()
{
	this->Search = new Emojidex::Service::Search();
	//this->transactor = new Emojidex::Transactor();
}

char Emojidex::Client::apiVersion()
{
	return 1;
}
