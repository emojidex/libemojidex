#include "indexes.h"
#include "transactor.h"
#include "rapidjson/document.h"

Emojidex::Service::Indexes::Indexes()
{
	this->codes = new Emojidex::Data::MojiCodes();
}

Emojidex::Service::Indexes::~Indexes()
{
	delete this->codes;
}

Emojidex::Data::MojiCodes* Emojidex::Service::Indexes::mojiCodes(string locale)
{
	if (this->codes->locale.compare(locale) == 0) {
		return this->codes;
	}

	Emojidex::Service::Transactor transactor;
	string response = transactor.get("moji_codes", {{"locale", locale}});
	this->codes->locale = locale;

	return this->codes;
}
