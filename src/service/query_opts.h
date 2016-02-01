#ifndef EMOJIDEX_SERVICE_SEARCH_CONDITIONS_H
#define EMOJIDEX_SERVICE_SEARCH_CONDITIONS_H

#include <unordered_map>

namespace Emojidex {
	namespace Service {
		class QueryOpts
		{
			private:
				std::unordered_map<std::string, std::string> conditions;
			public:
			QueryOpts();

			Emojidex::Service::QueryOpts page(unsigned int number);
		//	Emojidex::Service::QueryOpts* limit(unsigned int limit);
		//	Emojidex::Service::QueryOpts* username(std::string username);
		//	Emojidex::Service::QueryOpts* auth_token(std::string auth_token);

			
			Emojidex::Service::QueryOpts condition(std::string key, std::string value);

			std::string valueOf(std::string key);
		};
	}
}

#endif /* EMOJIDEX_SERVICE_SEARCH_CONDITIONS_H */
