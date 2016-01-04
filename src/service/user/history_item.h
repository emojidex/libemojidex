#ifndef EMOJIDEX_SERVICE_USER_HISTORY_ITEM_H
#define EMOJIDEX_SERVICE_USER_HISTORY_ITEM_H


#include <string>

namespace Emojidex {
	namespace Service {
		class HistoryItem {
			public:

			std::string emoji_code;
			unsigned int times_used;
			std::string last_used;

			HistoryItem(std::string emoji_code, unsigned int times_used, std::string last_used);
		};
	}
}

#endif /* EMOJIDEX_SERVICE_USER_HISTORY_ITEM_H */
