#ifndef EMOJIDEX_SERVICE_INDEXES_H
#define EMOJIDEX_SERVICE_INDEXES_H

#include "../data/moji_codes.h"
#include "../data/collection.h"
#include "collector.h"
#include "./user.h"

namespace Emojidex {
	namespace Service {
		//! Retrieves data from emojidex indexes
		class Indexes
		{
		private:
			Emojidex::Data::MojiCodes *codes;
			const Emojidex::Service::User *user;

			void fillMojiCodesFromJson(const std::string& src);
			void fillMojiCodesFromMsgPack(const std::string& src);

		public:
			Indexes();
			~Indexes();

			void setUser(const Emojidex::Service::User *user);

			/* NOTE: all calls default to locale = "en" and detailed = false */

			//=====================================================================================
			// Static Seeds
			// ============

			//! Get standard UTF emoji info in 3 compact forms
			Emojidex::Data::MojiCodes mojiCodes(std::string locale = DEFAULT_LOCALE);
			//! Get a collection of all standard UTF emoji
			Emojidex::Data::Collection utfEmoji(std::string locale = DEFAULT_LOCALE, bool detailed = true);
			//! Get a collection of all emojidex Extended emoji
			Emojidex::Data::Collection extendedEmoji(std::string locale = DEFAULT_LOCALE, bool detailed = true);
		  
			//=====================================================================================
			// Dynamic Indexes
			// ===============

			//! Get full emoji index (by score unless otherwise configured with conditions)
			Emojidex::Data::Collection emoji(unsigned int page = DEFAULT_PAGE,
					unsigned int limit = DEFAULT_LIMIT, bool detailed = false,
					Emojidex::Service::QueryOpts *conditions = NULL);

			//! Get Newest emoji
			Emojidex::Data::Collection newest(std::string auth_token = "",
					unsigned int page = DEFAULT_PAGE,
					unsigned int limit = DEFAULT_LIMIT, bool detailed = false);

			//! Get most Popular emoji
			Emojidex::Data::Collection popular(std::string auth_token = "",
					unsigned int page = DEFAULT_PAGE,
					unsigned int limit = DEFAULT_LIMIT, bool detailed = false);

			//! Get the emoji registered by a specific user (by username)
			Emojidex::Data::Collection userEmoji(std::string username,
					unsigned int page = DEFAULT_PAGE,
					unsigned int limit = DEFAULT_LIMIT, bool detailed = false);
		};
	}
}

#endif /* EMOJIDEX_SERVICE_INDEXES_H */
