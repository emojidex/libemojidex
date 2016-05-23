#ifndef EMOJIDEX_SERVICE_SEARCH_H
#define EMOJIDEX_SERVICE_SEARCH_H

#include "../data/collection.h"
#include "../libemojidex.h"
#include "./query_opts.h"
#include "./user.h"

#include <string>

namespace Emojidex {
	namespace Service {
		class Search
		{
		private:
			const Emojidex::Service::User *user;

		public:
			unsigned int current_page;

			Search();

			void setUser(const Emojidex::Service::User *user);

			Emojidex::Data::Collection term(const std::string code_cont, Emojidex::Service::QueryOpts *conditions = NULL);
			Emojidex::Data::Collection starting(std::string code_sw, Emojidex::Service::QueryOpts *conditions = NULL);
			Emojidex::Data::Collection ending(std::string code_ew, Emojidex::Service::QueryOpts *conditions = NULL);
			Emojidex::Data::Collection tags(std::string tags[], Emojidex::Service::QueryOpts *conditions = NULL);
			Emojidex::Data::Collection advanced(std::string code_cont, std::string categories[],
					std::string tags[], Emojidex::Service::QueryOpts *conditions = NULL);

			// Attempts to directly obtain emoji data by code
			// Returns a Data::Emoji object filled with the emoji info on success (the emoji is registered)
			// Returns an empty emoji object with only the code field filled on failure (the emoji is not registered)
			Emojidex::Data::Emoji find(std::string code, bool detailed = true);
		};
	}
}

#endif /* EMOJIDEX_SERVICE_SEARCH_H */
