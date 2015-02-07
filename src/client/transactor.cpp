#include "transactor.h"


Emojidex::Transactor::Transactor(exchange_info info_set)
{
	this->info = info_set;
	this->easy = new curl_easy();
}
