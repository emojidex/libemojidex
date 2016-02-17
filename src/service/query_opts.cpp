#include "query_opts.h"

#include <sstream>

Emojidex::Service::QueryOpts::QueryOpts()
{
	this->locale = "";
}

void Emojidex::Service::QueryOpts::setCollectionDefaults()
{
	this->conditions["page"] = std::to_string(1);
	this->conditions["limit"] = std::to_string(DEFAULT_LIMIT);
	this->conditions["detailed"] = "true";
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::page(unsigned int number)
{
	this->conditions["page"] = std::to_string(number);
	return *this;
}

unsigned int Emojidex::Service::QueryOpts::getPage()
{
	std::string val = getValue("page");
	if (val.compare("") == 0)
		return 0;
	return std::stoi(val);
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::limit(unsigned int value)
{
	this->conditions["limit"] = std::to_string(value);
	return *this;
}

unsigned int Emojidex::Service::QueryOpts::getLimit()
{
	std::string val = getValue("limit");
	if (val.compare("") == 0)
		return 0;
	return std::stoi(val);
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::detailed(bool detail)
{
	conditions["detailed"] = TF(detail);
	return *this;
}

bool Emojidex::Service::QueryOpts::getDetailed()
{
	std::string val = getValue("detailed");
	if (val.compare("") == 0)
		return true;

	bool val_bool;
	std::istringstream(val) >> std::boolalpha >> val_bool;
	return val_bool;
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::username(std::string username)
{
	this->conditions["username"] = username;
	return *this;
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::auth_token(std::string auth_token)
{
	this->conditions["auth_token"] = auth_token;
	return *this;
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::tag(std::string tag)
{
	this->tags.push_back(tag);
	return *this;
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::category(std::string category)
{
	this->categories.push_back(category);
	return *this;
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::condition(std::string key, std::string value)
{
	this->conditions[key] = value;
	return *this;
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::ext(std::string opt, std::string prefix)
{
	ext_opts = ext_opts + prefix + opt;
	return *this;
}

std::string Emojidex::Service::QueryOpts::getValue(std::string key)
{
	std::unordered_map<std::string, std::string>::const_iterator pos = this->conditions.find(key);

	if (pos == this->conditions.end())
		return "";

	return pos->second;
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::parseUnorderedMap(std::unordered_map<std::string, std::string> source_map)
{
	for (auto it = source_map.begin(); it != source_map.end(); it++)
		this->condition(it->first, it->second);
	return *this;
}

std::string Emojidex::Service::QueryOpts::to_string()
{
	std::stringstream qss;

	qss << "?"; //prefix

	if (locale.compare("") != 0)
		qss << "&locale=" << locale;

	if (getValue("limit").compare("") != 0)
		qss << "&limit=" << getValue("limit");

	if (getValue("page").compare("") != 0)
		qss << "&page=" << getValue("page");

	if (getValue("detailed").compare("") != 0)
		qss << "&detailed=" << getValue("detailed");

	if (getValue("auth_token").compare("") != 0)
		qss << "&auth_token=" << getValue("auth_token");

	if (getValue("username").compare("") != 0)
		qss << "&username=" << getValue("username");

	std::vector<std::string>::iterator item;
	for (item = tags.begin(); item < tags.end(); item++)
		qss << "&tags[]=" << *item;

	for (item = categories.begin(); item < categories.end(); item++)
		qss << "&categories[]=" << *item;

	if (ext_opts.compare("") != 0)
		qss << ext_opts;
	
	return qss.str();
}
