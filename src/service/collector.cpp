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
	string response = transactor.get(name, {{"locale", locale}, 
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
	string response = transactor.get(name, {{"limit", lexical_cast<string>(limit)}, 
			{"page", lexical_cast<string>(page)}, {"detailed", TF(detailed)}});

	collect.mergeJSON(response);

	return collect;
}

Emojidex::Data::Collection Emojidex::Service::Collector::getCollection(Emojidex::Data::Collection collect)
{
	Emojidex::Service::Transactor transactor;
	
	string response = "";
	if (collect.token.compare("") != 0) {
		response = transactor.get(collect.endpoint, {{"limit", lexical_cast<string>(collect.limit)}, 
			{"page", lexical_cast<string>(collect.page)}, {"detailed", TF(collect.detailed)}});
	} else {
		response = transactor.get(collect.endpoint, {{"limit", lexical_cast<string>(collect.limit)}, 
			{"page", lexical_cast<string>(collect.page)}, {"detailed", TF(collect.detailed)},
			{"auth_token", collect.token}});
	}

	collect.mergeJSON(response);

	return collect;
}
