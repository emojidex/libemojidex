#include "search.h"
#include "transactor.h"

Emojidex::Service::Search::Search()
{
	this->current_page = 0;
}


Emojidex::Data::Collection Emojidex::Service::Search::term(const std::string code_cont, const std::unordered_map<std::string, std::string>& conditions)
{
	Emojidex::Service::QueryOpts opts;
	opts.parseUnorderedMap(conditions);
	return term(code_cont, &opts);
}

Emojidex::Data::Collection Emojidex::Service::Search::term(std::string code_cont, Emojidex::Service::QueryOpts *conditions)
{
	Emojidex::Data::Collection result;

	if (conditions == NULL)
		conditions = new Emojidex::Service::QueryOpts();

	result.opts = *conditions;
	result.endpoint = "search/emoji";
	result.more();

	return result;
}

Emojidex::Data::Emoji Emojidex::Service::Search::find(std::string code, bool detailed)
{
	code = Emojidex::escapeCode(Emojidex::unencapsulateCode(code));

	Emojidex::Service::Transactor transactor;
	std::string endpoint = "emoji/" + code;
	std::string response = transactor.GET(endpoint, {{"detailed", TF(detailed)}});
  
	// Create emoji object.
	Emojidex::Data::Emoji result;
	result.fillFromJSONString(response);

	return result;
}
