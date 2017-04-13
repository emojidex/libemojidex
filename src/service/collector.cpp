#include "collector.h"
#include "transactor.h"
#include "rapidjson/document.h"

#include <sstream>

using namespace std;
using namespace Emojidex::Data;


Emojidex::Data::Collection Emojidex::Service::Collector::getStaticCollection(string name,
		string locale, bool detailed)
{
	Emojidex::Data::Collection collect = Emojidex::Data::Collection();

	collect.endpoint = name;
	collect.opts.locale(locale);
	collect.opts.detailed(detailed);

	Emojidex::Service::Transactor transactor;
	string response = transactor.GET(name, {{"locale", locale},
			{"detailed", TF(detailed)}}, NULL, true);

	collect.mergeMsgPack(response);

	return collect;
}


Emojidex::Data::Collection Emojidex::Service::Collector::getDynamicCollection(string name,
		unsigned int page, unsigned int limit, bool detailed, Emojidex::Service::QueryOpts *conditions)
{
	Emojidex::Data::Collection collect = Emojidex::Data::Collection();
	collect.endpoint = name;
	if (conditions != NULL)
		collect.opts = *conditions;
	collect.opts.detailed(detailed);
	collect.opts.limit(limit);
	collect.opts.page(page);

	Emojidex::Service::Transactor transactor;
	string response = transactor.GET(collect.endpoint, collect.opts, NULL, true);

	collect.mergeMsgPack(response);

	return collect;
}

Emojidex::Data::Collection Emojidex::Service::Collector::getAuthorizedDynamicCollection(string name,
		std::string auth_token, unsigned int page, unsigned int limit, bool detailed, Emojidex::Service::QueryOpts *conditions)
{
	Emojidex::Data::Collection collect = Emojidex::Data::Collection();
	collect.endpoint = name;
	if (conditions != NULL)
		collect.opts = *conditions;
	collect.opts.detailed(detailed);
	collect.opts.limit(limit);
	collect.opts.page(page);
	collect.opts.auth_token(auth_token);

	return getCollection(collect);
}

Emojidex::Data::Collection Emojidex::Service::Collector::getCollection(Emojidex::Data::Collection collect)
{
	Emojidex::Service::Transactor transactor;

	string response = "";
	response = transactor.GET(collect.endpoint, collect.opts, NULL, true);

	collect.mergeMsgPack(response);

	return collect;
}
