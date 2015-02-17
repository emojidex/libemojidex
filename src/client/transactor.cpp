#include "transactor.h"

Emojidex::Transactor::Transactor(exchange_info info_set)
{
	this->info = info_set;
	this->api_addr = this->info.api_protocol + "://" + this->info.api_url;
}

string Emojidex::Transactor::get(string endpoint, string opts)
{
	string path = api_addr + endpoint;
	ostream request_stream;
	request_stream << "GET" << path <<
}
