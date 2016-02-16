#ifndef EMOJIDEX_SERVICE_SEARCH_CONDITIONS_H
#define EMOJIDEX_SERVICE_SEARCH_CONDITIONS_H

#include <vector>
#include <unordered_map>

namespace Emojidex {
	namespace Service {
		class QueryOpts
		{
			public:
			QueryOpts();

			std::unordered_map<std::string, std::string> conditions;
			std::vector<std::string> tags;

			Emojidex::Service::QueryOpts page(unsigned int number = 0);
			Emojidex::Service::QueryOpts limit(unsigned int value = 50);
			Emojidex::Service::QueryOpts username(std::string username = "");
			Emojidex::Service::QueryOpts auth_token(std::string auth_token = "");

			Emojidex::Service::QueryOpts tag(std::string tag);

			Emojidex::Service::QueryOpts condition(std::string key, std::string value);

			std::string valueOf(std::string key);

			Emojidex::Service::QueryOpts parseUnorderedMap(std::unordered_map<std::string, std::string> source_map);
			std::string to_string();
		};
	}
}

#endif /* EMOJIDEX_SERVICE_SEARCH_CONDITIONS_H */
