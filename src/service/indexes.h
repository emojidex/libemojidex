#ifndef EMOJIDEX_SERVICE_INDEXES_H
#define EMOJIDEX_SERVICE_INDEXES_H

#include "../data/moji_codes.h"
#include "../data/collection.h"
#include "../defs.h"
#include "rapidjson/document.h"

namespace Emojidex {
	namespace Service {
		// Retrieves data from emojidex indexes
		class Indexes
		{
		private:
			Emojidex::Data::MojiCodes *codes;
			// service methods
			static void defaultLocale(std::string *object_locale, std::string *locale);
			static Emojidex::Data::Collection getStaticCollection(std::string name, std::string locale, 
					bool detailed);
			static Emojidex::Data::Collection getDynamicCollection(std::string name, unsigned int page,
					unsigned int limit, bool detailed);
		public:
			Indexes();
			~Indexes();


			/* NOTE: all calls default to locale = "en" and detailed = false */

			//=====================================================================================
			// Static Seeds
			// ============

			// Get standard UTF emoji info in 3 compact forms
			Emojidex::Data::MojiCodes mojiCodes(std::string locale = "");
			// Get a collection of all standard UTF emoji
			Emojidex::Data::Collection utfEmoji(std::string locale = "", bool detailed = false);
			// Get a collection of all emojidex Extended emoji
			Emojidex::Data::Collection extendedEmoji(std::string locale = "", bool detailed = false);
		  
			//=====================================================================================
			// Dynamic Indexes
			// ===============


			static Emojidex::Data::Collection nextPage(Emojidex::Data::Collection collection);

			// Get full emoji index by score
			Emojidex::Data::Collection emoji(unsigned int page = DEFAULT_PAGE, 
					unsigned int limit = DEFAULT_LIMIT, bool detailed = false);
			// Get Newest emoji
			Emojidex::Data::Collection newest(unsigned int page = DEFAULT_PAGE,
					unsigned int limit = DEFAULT_LIMIT, bool detailed = false);

			// Get most Popular emoji
			Emojidex::Data::Collection popular(unsigned int page = DEFAULT_PAGE,
					unsigned int limit = DEFAULT_LIMIT, bool detailed = false);
		};
	}
}

#endif /* EMOJIDEX_SERVICE_INDEXES_H */
