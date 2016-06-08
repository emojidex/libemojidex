#ifndef EMOJIDEX_SERVICE_COLLECTOR_H
#define EMOJIDEX_SERVICE_COLLECTOR_H

#include "./query_opts.h"
#include "../data/collection.h"

namespace Emojidex {
	namespace Service {
		//! Provides generic calls to fill a Collection from an API endpoint
		class Collector
		{
		public:
			//! Gets a static collection from seed endpoints (non paginated, limited query options)
			static Emojidex::Data::Collection getStaticCollection(std::string name, std::string locale = DEFAULT_LOCALE,
				bool detailed = true);
			//! Gets a dynamic collection (paginated, queryable/customizable)
			static Emojidex::Data::Collection getDynamicCollection(std::string name, unsigned int page,
				unsigned int limit, bool detailed, Emojidex::Service::QueryOpts *conditions = NULL);
			//! Gets a dynamic collection with forced auth credentials
			static Emojidex::Data::Collection getAuthorizedDynamicCollection(std::string name,
				std::string auth_token, 
				unsigned int page, unsigned int limit, bool detailed,
				Emojidex::Service::QueryOpts *conditions = NULL);
			//! Gets a collection from an instantiated collection object
			static Emojidex::Data::Collection getCollection(Emojidex::Data::Collection collect);
		};
	}
}

#endif /* EMOJIDEX_SERVICE_COLLECTOR_H */
