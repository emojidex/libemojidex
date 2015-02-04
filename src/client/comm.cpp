#include "comm.h"

Emojidex::Comm::Comm()
{
	asio::io_service io_service;
	sock = new ip::tcp::socket(io_service);
	resolver = new ip::tcp::resolver(io_service);
	query = new ip::tcp::resolver::query(this->info.api_url, this->info.api_protocol);
}

Emojidex::Comm::Comm(comm_info info)
{
	this->info = info;
}
