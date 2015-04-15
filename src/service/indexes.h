#ifndef EMOJIDEX_SERVICE_INDEXES_H
#define EMOJIDEX_SERVICE_INDEXES_H

#include "../data/moji_codes.h"
#include "../data/emoji.h"
#include "../data/collection.h"

namespace Emojidex {
	namespace Service {
		// Retrieves data from emojidex indexes
		class Indexes
		{
		private:
			Emojidex::Data::MojiCodes *codes;
		public:
			Indexes();
			~Indexes();

			Emojidex::Data::MojiCodes mojiCodes(string locale = "");
      Emojidex::Data::Collection utfEmoji(string locale = "", bool detailed = false);
      Emojidex::Data::Collection extendedEmoji(string locale = "", bool detailed = false);
      
		};
	}
}

#endif /* EMOJIDEX_SERVICE_INDEXES_H */
