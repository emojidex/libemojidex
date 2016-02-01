#include "collector.h"
#include "transactor.h"
#include "rapidjson/document.h"

using namespace std;
using namespace Emojidex::Data;

const string Emojidex::Service::Collector::DefaultLocale = DEFAULT_LOCALE;

void Emojidex::Service::Collector::defaultLocale(string *object_locale, string *locale)
{
	if (locale->compare("") == 0) { // default arg
		if (object_locale->compare("") == 0) { // if not already defined 
			*locale = "en"; // default to english
		} else {
			*locale = *object_locale;
		}
	}
}

Emojidex::Data::Collection Emojidex::Service::Collector::getStaticCollection(string name, 
		string locale, bool detailed)
{
	Emojidex::Data::Collection collect = Emojidex::Data::Collection();
	defaultLocale(&collect.locale, &locale);

	Emojidex::Service::Transactor transactor;
	string response = transactor.GET(name, {{"locale", locale}, 
			{"detailed", TF(detailed)}});

	collect.mergeJSON(response);

	collect.locale = locale;
	collect.endpoint = name;
	collect.detailed = detailed;

	return collect;
}


Emojidex::Data::Collection Emojidex::Service::Collector::getDynamicCollection(string name, 
		unsigned int page, unsigned int limit, bool detailed)
{
	Emojidex::Data::Collection collect = Emojidex::Data::Collection();
	collect.detailed = detailed;
	collect.endpoint = name;
	collect.limit = limit;
	collect.page = page;

	Emojidex::Service::Transactor transactor;
	string response = transactor.GET(name, {{"limit", std::to_string(limit)}, 
			{"page", std::to_string(page)}, {"detailed", TF(detailed)}});

	collect.mergeJSON(response);

	return collect;
}

Emojidex::Data::Collection Emojidex::Service::Collector::getAuthorizedDynamicCollection(string name, 
		std::string auth_token, unsigned int page, unsigned int limit, bool detailed)
{
	Emojidex::Data::Collection collect = Emojidex::Data::Collection();
	collect.detailed = detailed;
	collect.endpoint = name;
	collect.limit = limit;
	collect.page = page;
	collect.auth_token = auth_token;

	Emojidex::Service::Transactor transactor;
	string response = transactor.GET(name, {{"limit", std::to_string(limit)},
			{"page", std::to_string(page)}, {"detailed", TF(detailed)}});

	collect.mergeJSON(response);

	return collect;
}

Emojidex::Data::Collection Emojidex::Service::Collector::getCollection(Emojidex::Data::Collection collect)
{
	Emojidex::Service::Transactor transactor;
	
	string response = "";
	if (collect.auth_token.compare("") != 0) {
		response = transactor.GET(collect.endpoint, {{"limit", std::to_string(collect.limit)}, 
				{"page", std::to_string(collect.page)}, {"detailed", TF(collect.detailed)}});
	} else {
		response = transactor.GET(collect.endpoint, {{"limit", std::to_string(collect.limit)}, 
				{"page", std::to_string(collect.page)}, {"detailed", TF(collect.detailed)},
				{"auth_token", collect.auth_token}});
	}

	collect.mergeJSON(response);

	return collect;
}
