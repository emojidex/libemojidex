#include "conditions.h"

Emojidex::Service::SearchConditions::SearchConditions()
{
}

Emojidex::Service::SearchConditions* Emojidex::Service::SearchConditions::page(unsigned int number)
{
	this->conditions["page"] = std::to_string(number);
	return this;
}
