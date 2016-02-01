#ifndef EMOJIDEX_SERVICE_SEARCH_CONDITIONS_H
#define EMOJIDEX_SERVICE_SEARCH_CONDITIONS_H

#include <unordered_map>

namespace Emojidex {
	namespace Service {
		class SearchConditions
		{
			private:
				std::unordered_map<std::string, std::string> conditions;
			public:
			SearchConditions();

			Emojidex::Service::SearchConditions* page(unsigned int number);
		//	Emojidex::Service::SearchConditions* limit(unsigned int limit);
		//	Emojidex::Service::SearchConditions* username(std::string username);
		//	Emojidex::Service::SearchConditions* auth_token(std::string auth_token);

			
			Emojidex::Service::SearchConditions* condition(std::string key, std::string value);
		};
	}
}

#endif /* EMOJIDEX_SERVICE_SEARCH_CONDITIONS_H */
