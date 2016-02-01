#include "query_opts.h"

Emojidex::Service::QueryOpts::QueryOpts()
{
	//this->conditions["page"] = std::to_string(0);
	//this->conditions["limit"] = std::to_string(Emojidex::Service::Collector::DefaultLimit);
}

Emojidex::Service::QueryOpts Emojidex::Service::QueryOpts::page(unsigned int number)
{
	this->conditions["page"] = std::to_string(number);
	return *this;
}

Emojidex::Service::QueryOpts Emojidex::Service::QueryOpts::condition(std::string key, std::string value)
{
	this->conditions[key] = value;
	return *this;
}

std::string Emojidex::Service::QueryOpts::valueOf(std::string key)
{
	std::unordered_map<std::string, std::string>::const_iterator pos = this->conditions.find(key);

	if (pos == this->conditions.end())
		return "";

	return pos->second;
}
