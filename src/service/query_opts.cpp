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

Emojidex::Service::QueryOpts Emojidex::Service::QueryOpts::limit(unsigned int value)
{
	this->conditions["limit"] = std::to_string(value);
	return *this;
}

Emojidex::Service::QueryOpts Emojidex::Service::QueryOpts::username(std::string username)
{
	this->conditions["username"] = username;
	return *this;
}

Emojidex::Service::QueryOpts Emojidex::Service::QueryOpts::auth_token(std::string auth_token)
{
	this->conditions["auth_token"] = auth_token;
	return *this;
}

Emojidex::Service::QueryOpts Emojidex::Service::QueryOpts::tag(std::string tag)
{
	//this->tags.push_back(tag);
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
