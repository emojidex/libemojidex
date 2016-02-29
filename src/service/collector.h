#ifndef EMOJIDEX_SERVICE_COLLECTOR_H
#define EMOJIDEX_SERVICE_COLLECTOR_H

#include "./query_opts.h"
#include "../data/collection.h"

namespace Emojidex {
	namespace Service {
		// Provides generic calls to fill a Collection from an API endpoint
		class Collector
		{
		public:
			static Emojidex::Data::Collection getStaticCollection(std::string name, std::string locale = DEFAULT_LOCALE,
				bool detailed = true);
			static Emojidex::Data::Collection getDynamicCollection(std::string name, unsigned int page,
				unsigned int limit, bool detailed, std::string ext_args = "");
			static Emojidex::Data::Collection getAuthorizedDynamicCollection(std::string name,
				std::string auth_token, 
				unsigned int page, unsigned int limit, bool detailed, std::string ext_args = "");
			static Emojidex::Data::Collection getCollection(Emojidex::Data::Collection collect);
		};
	}
}

#endif /* EMOJIDEX_SERVICE_COLLECTOR_H */
