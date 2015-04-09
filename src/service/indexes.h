#ifndef EMOJIDEX_SERVICE_INDEXES_H
#define EMOJIDEX_SERVICE_INDEXES_H

#include "../data/moji_codes.h"

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

			Emojidex::Data::MojiCodes* mojiCodes(string locale = "");
		};
	}
}

#endif /* EMOJIDEX_SERVICE_INDEXES_H */
