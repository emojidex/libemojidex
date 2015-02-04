#include "search.h"

#include <iostream>
#include <boost/asio.hpp>

Emojidex::SearchClient::SearchClient()
{
	this->current_page = 0;
}

std::string Emojidex::SearchClient::term(std::string term)
{
	return "";
}
