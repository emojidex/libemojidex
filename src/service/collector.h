#ifndef EMOJIDEX_SERVICE_COLLECTOR_H
#define EMOJIDEX_SERVICE_COLLECTOR_H

#define DEFAULT_LOCALE "en"
#define DEFAULT_PAGE 1
#define DEFAULT_LIMIT 50
#define TF(bv) ((bv)?"true":"false")

#include "../data/collection.h"
using namespace Emojidex::Data;

namespace Emojidex {
	namespace Service {
		// Provides generic calls to fill a Collection from an API endpoint
		class Collector
		{
		public:
			static const string DefaultLocale;
			static const unsigned int DefaultPage = DEFAULT_PAGE;
			static const unsigned int DefaultLimit = DEFAULT_LIMIT;

			static void defaultLocale(std::string *object_locale, std::string *locale);
			static Collection getStaticCollection(std::string name, std::string locale,
				bool detailed);
			static Collection getDynamicCollection(std::string name, unsigned int page,
				unsigned int limit, bool detailed);
			static Collection getCollection(Collection collect);
		};
	}
}

#endif /* EMOJIDEX_SERVICE_COLLECTOR_H */
