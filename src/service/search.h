#ifndef EMOJIDEX_SERVICE_SEARCH_H
#define EMOJIDEX_SERVICE_SEARCH_H

#include "../data/collection.h"

#include <string>

namespace Emojidex {
	namespace Service {
		class Search
		{
		public:
			unsigned int current_page;

			Search();
			Emojidex::Data::Collection term(std::string term);
		};
	}
}

#endif /* EMOJIDEX_SERVICE_SEARCH_H */
