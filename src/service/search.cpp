#include "search.h"
#include "transactor.h"

#include <regex>

namespace
{
  std::string escape_regex(const std::string& src)
  {
    std::regex regex("\\(|\\)|%28|%29");
    return std::regex_replace(src, regex, "\\$0");
  }

  bool is_logged_in(const Emojidex::Service::User *user)
  {
  	return user != NULL && !user->auth_token.empty();
  }
}

Emojidex::Service::Search::Search()
	: user(NULL)
{
	this->current_page = 0;
}

void Emojidex::Service::Search::setUser(const Emojidex::Service::User *user)
{
	this->user = user;
}

Emojidex::Data::Collection Emojidex::Service::Search::term(std::string code_cont, Emojidex::Service::QueryOpts *conditions)
{
	Emojidex::Data::Collection result;

	result.opts = conditions != NULL ? *conditions : Emojidex::Service::QueryOpts();
	result.opts.page(result.opts.getPage() - 1);
	result.endpoint = "search/emoji";
	result.opts.ext("code_cont=" + escape_regex(code_cont));
	if(is_logged_in(user))
		result.opts.auth_token(user->auth_token);
	result.more();

	return result;
}

Emojidex::Data::Collection Emojidex::Service::Search::starting(std::string code_sw, Emojidex::Service::QueryOpts *conditions)
{
	Emojidex::Data::Collection result;

	result.opts = conditions != NULL ? *conditions : Emojidex::Service::QueryOpts();
	result.opts.page(result.opts.getPage() - 1);
	result.endpoint = "search/emoji";
	result.opts.ext("code_sw=" + escape_regex(code_sw));
	if(is_logged_in(user))
		result.opts.auth_token(user->auth_token);
	result.more();

	return result;
}

Emojidex::Data::Collection Emojidex::Service::Search::ending(std::string code_ew, Emojidex::Service::QueryOpts *conditions)
{
	Emojidex::Data::Collection result;

	result.opts = conditions != NULL ? *conditions : Emojidex::Service::QueryOpts();
	result.opts.page(result.opts.getPage() - 1);
	result.endpoint = "search/emoji";
	result.opts.ext("code_ew=" + escape_regex(code_ew));
	if(is_logged_in(user))
		result.opts.auth_token(user->auth_token);
	result.more();

	return result;
}


Emojidex::Data::Collection Emojidex::Service::Search::tags(std::string tags[], Emojidex::Service::QueryOpts *conditions)
{
	Emojidex::Data::Collection result;

	result.opts = conditions != NULL ? *conditions : Emojidex::Service::QueryOpts();
	result.opts.page(result.opts.getPage() - 1);
	result.endpoint = "search/emoji";
	for (unsigned int i = 0; i < tags->size(); i++)
		result.opts.tag(tags[i]);
	if(is_logged_in(user))
		result.opts.auth_token(user->auth_token);
	result.more();

	return result;
}

Emojidex::Data::Collection Emojidex::Service::Search::advanced(std::string code_cont, std::string categories[],
	std::string tags[], Emojidex::Service::QueryOpts *conditions)
{
	Emojidex::Data::Collection result;

	result.opts = conditions != NULL ? *conditions : Emojidex::Service::QueryOpts();
	result.opts.page(result.opts.getPage() - 1);
	result.endpoint = "search/emoji";
	result.opts.ext("code_cont=" + escape_regex(code_cont));
	for (unsigned int i = 0; i < tags->size(); i++)
		result.opts.tag(tags[i]);
	for (unsigned int i = 0; i < categories->size(); i++)
		result.opts.category(categories[i]);
	if(is_logged_in(user))
		result.opts.auth_token(user->auth_token);
	result.more();

	return result;
}

Emojidex::Data::Emoji Emojidex::Service::Search::find(std::string code, bool detailed)
{
	code = Emojidex::escapeCode(Emojidex::unencapsulateCode(code));

	Emojidex::Service::Transactor transactor;
	std::string endpoint = "emoji/" + code;
	std::string response = is_logged_in(user) ?
		transactor.GET(endpoint, {{"detailed", TF(detailed)}, {"auth_token", user->auth_token}}):
		transactor.GET(endpoint, {{"detailed", TF(detailed)}});
  
	// Create emoji object.
	Emojidex::Data::Emoji result;
	result.fillFromJSONString(response);

	return result;
}
