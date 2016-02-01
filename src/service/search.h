#ifndef EMOJIDEX_SERVICE_SEARCH_H
#define EMOJIDEX_SERVICE_SEARCH_H

#include "../data/collection.h"
#include "./search/conditions.h"

#include <string>

namespace Emojidex {
	namespace Service {
		class Search
		{
		public:
			unsigned int current_page;

			Search();

			Emojidex::Data::Collection term(std::string code_cont, Emojidex::Service::SearchConditions conditions);
		//	Emojidex::Data::Collection starting(std::string code_sw, Emojidex::Service::SearchConditions conditions);
		//	Emojidex::Data::Collection ending(std::string code_ew, Emojidex::Service::SearchConditions conditions);
		//	Emojidex::Data::Collection tags(std::string *tags, Emojidex::Service::SearchConditions conditions);
		//	Emojidex::Data::Collection advanced(std::string code_cont, std::string *categories, std::string *tags, Emojidex::Service::SearchConditions conditions);
		};
	}
}

#endif /* EMOJIDEX_SERVICE_SEARCH_H */
