#ifndef EMOJIDEX_SERVICE_SEARCH_H
#define EMOJIDEX_SERVICE_SEARCH_H

#include "../data/collection.h"
#include "../libemojidex.h"
#include "./query_opts.h"
#include "./user.h"

#include <string>
#include <vector>

namespace Emojidex {
	namespace Service {
		//! Search functionality for the emojidex service
		class Search
		{
		private:
			const Emojidex::Service::User *user;

		public:
			Search();

			//! Sets user for authorized search options such as ordering and enabling R-18 results
			void setUser(const Emojidex::Service::User *user);

			//! Search within emoji short codes for a term (EG: 'car' will include results like 'blue_car')
			Emojidex::Data::Collection term(const std::string code_cont, Emojidex::Service::QueryOpts *conditions = NULL);
			//! Search within emoji short codes for codes that start with a term
			Emojidex::Data::Collection starting(std::string code_sw, Emojidex::Service::QueryOpts *conditions = NULL);
			//! Search within emoji short codes for codes that end with a term
			Emojidex::Data::Collection ending(std::string code_ew, Emojidex::Service::QueryOpts *conditions = NULL);
			//! Search for emoji with all the assigned tags. The tags array is exclusive in that more tags narrow down results.
			Emojidex::Data::Collection tags(const std::vector<std::string> &tags, Emojidex::Service::QueryOpts *conditions = NULL);
			//! Compound search for a term, included in one of the given categories, with all of the given tags.
			Emojidex::Data::Collection advanced(std::string code_cont, const std::vector<std::string> &categories,
					const std::vector<std::string> &tags, Emojidex::Service::QueryOpts *conditions = NULL);

			//" Attempts to directly obtain emoji data by code
			/*!
			 * Returns a Data::Emoji object filled with the emoji info on success (the emoji is registered)\n
			 * Returns an empty emoji object with only the code field filled on failure (the emoji is not registered)
			 */
			Emojidex::Data::Emoji find(std::string code, bool detailed = true);
		};
	}
}

#endif /* EMOJIDEX_SERVICE_SEARCH_H */
