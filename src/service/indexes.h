#ifndef EMOJIDEX_SERVICE_INDEXES_H
#define EMOJIDEX_SERVICE_INDEXES_H

#include "../data/moji_codes.h"
#include "../data/emoji.h"
#include "../data/collection.h"

#define DEFAULT_LOCALE "en"
#define DEFAULT_PAGE 0
#define DEFAULT_LIMIT 50
#define TF(bv) ((bv)?"true":"false")

namespace Emojidex {
	namespace Service {
		// Retrieves data from emojidex indexes
		class Indexes
		{
		private:
			Emojidex::Data::MojiCodes *codes;
			static void defaultLocale(string *object_locale, string *locale);
			static Emojidex::Data::Collection getStaticCollection(string name, string locale, 
					bool detailed);
			static Emojidex::Data::Collection getDynamicCollection(string name, unsigned int limit, 
					unsigned int page, bool detailed);
		public:
			Indexes();
			~Indexes();

			/* NOTE: all calls default to locale = "en" and detailed = false */

			//=====================================================================================
			// Static Seeds
			// ============

			// Get standard UTF emoji info in 3 compact forms
			Emojidex::Data::MojiCodes mojiCodes(string locale = "");
			// Get a collection of all standard UTF emoji
			Emojidex::Data::Collection utfEmoji(string locale = "", bool detailed = false);
			// Get a collection of all emojidex Extended emoji
			Emojidex::Data::Collection extendedEmoji(string locale = "", bool detailed = false);
		  
			//=====================================================================================
			// Dynamic Indexes
			// ===============


			static Emojidex::Data::Collection nextPage(Emojidex::Data::Collection collection);

			// Get full emoji index by score
			Emojidex::Data::Collection index(unsigned int limit = DEFAULT_LIMIT, 
					unsigned int page = DEFAULT_PAGE, bool detailed = false);
			// Get Newest emoji
			Emojidex::Data::Collection newest(unsigned int limit = DEFAULT_LIMIT, 
					unsigned int page = DEFAULT_PAGE, bool detailed = false);

			// Get most Popular emoji
		};
	}
}

#endif /* EMOJIDEX_SERVICE_INDEXES_H */
