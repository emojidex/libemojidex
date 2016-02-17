#ifndef EMOJIDEX_SERVICE_SEARCH_CONDITIONS_H
#define EMOJIDEX_SERVICE_SEARCH_CONDITIONS_H

#include <vector>
#include <unordered_map>

#define DEFAULT_LOCALE "en"
#define DEFAULT_PAGE 1
#define DEFAULT_LIMIT 50
#define TF(bv) ((bv)?"true":"false")

namespace Emojidex {
	namespace Service {
		class QueryOpts
		{
			public:
			QueryOpts();

			std::string locale;
			std::unordered_map<std::string, std::string> conditions;
			std::vector<std::string> tags;
			std::vector<std::string> categories;

			// Sets defaults for a collection
			void setCollectionDefaults();

			// Chain method to set "page" by unsigned int
			Emojidex::Service::QueryOpts& page(unsigned int number = 0);
			// Gets current value of "page" or returns default of 0 if not set
			// DOES NOT set value of "page" if page is not set
			unsigned int getPage();

			// Chain method to set "limit" by unsigned int
			Emojidex::Service::QueryOpts& limit(unsigned int value = DEFAULT_LIMIT);
			// Gets current value of "limit" or returns default (50) if not set
			// DOES NOT set value of "limit" if limit is not set
			unsigned int getLimit();

			// Chain method to set "detailed" by bool
			Emojidex::Service::QueryOpts& detailed(bool detail = true);
			// Gets current value of "default" or returns true if not set
			// DOES NOT set value of "default" if default is not set
			bool getDetailed();

			// Chain method to set "username"
			Emojidex::Service::QueryOpts& username(std::string username = "");

			// Chain method to set "auth_token"
			Emojidex::Service::QueryOpts& auth_token(std::string auth_token = "");

			// Chain method to add a tag string to the tags vector
			Emojidex::Service::QueryOpts& tag(std::string tag);

			// Chain method to add a category string to the categories vector
			Emojidex::Service::QueryOpts& category(std::string category);

			// Chain method to set a custom query key/variable and value
			Emojidex::Service::QueryOpts& condition(std::string key, std::string value);

			// Opts string that is appended to the end of a query
			std::string ext_opts;
			// Adds an opt to the ext_opts string with a prefixed "&" (or custom prefix when specified)
			Emojidex::Service::QueryOpts& ext(std::string opt, std::string prefix = "");

			std::string getValue(std::string key);

			Emojidex::Service::QueryOpts& parseUnorderedMap(std::unordered_map<std::string, std::string> source_map);
			std::string to_string();
		};
	}
}

#endif /* EMOJIDEX_SERVICE_SEARCH_CONDITIONS_H */
