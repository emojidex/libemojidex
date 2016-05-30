#include "query_opts.h"

#include <sstream>

Emojidex::Service::QueryOpts::QueryOpts()
{
	setCollectionDefaults();
}

void Emojidex::Service::QueryOpts::setCollectionDefaults()
{
	(*this)
		.locale()
		.page()
		.limit()
		.detailed()
		.username()
		.auth_token()
		.clearTags()
		.clearCategories()
		.clearExt()
		;
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::locale(const std::string &locale)
{
	_locale = locale;
	return *this;
}

const std::string& Emojidex::Service::QueryOpts::getLocale() const
{
	return _locale;
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::page(unsigned int number)
{
	_page = number;
	return *this;
}

unsigned int Emojidex::Service::QueryOpts::getPage() const
{
	return _page;
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::limit(unsigned int value)
{
	_limit = value;
	return *this;
}

unsigned int Emojidex::Service::QueryOpts::getLimit() const
{
	return _limit;
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::detailed(bool detail)
{
	_detailed = detail;
	return *this;
}

bool Emojidex::Service::QueryOpts::getDetailed() const
{
	return _detailed;
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::username(const std::string &username)
{
	_username = username;
	return *this;
}

const std::string& Emojidex::Service::QueryOpts::getUsername() const
{
	return _username;
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::auth_token(const std::string &auth_token)
{
	_auth_token = auth_token;
	return *this;
}

const std::string& Emojidex::Service::QueryOpts::getAuthToken() const
{
	return _auth_token;
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::tag(const std::string &tag)
{
	if (tag.empty() == false)
		this->_tags.push_back(tag);
	return *this;
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::clearTags()
{
	_tags.clear();
	return *this;
}

const std::vector<std::string>& Emojidex::Service::QueryOpts::getTags() const
{
	return _tags;
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::category(const std::string &category)
{
	this->_categories.push_back(category);
	return *this;
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::clearCategories()
{
	_categories.clear();
	return *this;
}

const std::vector<std::string>& Emojidex::Service::QueryOpts::getCategories() const
{
	return _categories;
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::ext(const std::string &opt, const std::string &prefix)
{
	_ext_opts += prefix + opt;
	return *this;
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::clearExt()
{
	_ext_opts.clear();
	return *this;
}

const std::string& Emojidex::Service::QueryOpts::getExt() const
{
	return _ext_opts;
}

Emojidex::Service::QueryOpts& Emojidex::Service::QueryOpts::parseUnorderedMap(const std::unordered_map<std::string, std::string> &source_map)
{
	for (auto it = source_map.begin(); it != source_map.end(); it++)
	{
		const std::string &key = it->first;
		const std::string &value = it->second;
		
		if(key.compare("page") == 0)
			_page = value.empty() ? DEFAULT_PAGE : std::stoi(value);
		else if(key.compare("limit") == 0)
			_limit = value.empty() ? DEFAULT_LIMIT : std::stoi(value);
		else if(key.compare("detailed") == 0)
			_detailed = (value.compare("false") == 0) ? false : true;
		else if(key.compare("username") == 0)
			_username = value;
		else if(key.compare("auth_token") == 0)
			_auth_token = value;
		else
			ext(key + "=" + value);
	}
	return *this;
}

std::string Emojidex::Service::QueryOpts::to_string() const
{
	std::stringstream qss;

	qss << "?"; //prefix

	if ( !_locale.empty() )
		qss << "&locale=" << _locale;

	qss << "&limit=" << _limit
			<< "&page=" << _page
			<< "&detailed=" << TF(_detailed);

	if ( !_auth_token.empty() )
		qss << "&auth_token=" << _auth_token;

	if ( !_username.empty() )
		qss << "&username=" << _username;

	std::vector<std::string>::const_iterator item;
	for (item = _tags.begin(); item < _tags.end(); item++)
		qss << "&tags[]=" << *item;

	for (item = _categories.begin(); item < _categories.end(); item++)
		qss << "&categories[]=" << *item;

	if ( !_ext_opts.empty() )
		qss << _ext_opts;
	
	return qss.str();
}
