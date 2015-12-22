#ifndef EMOJIDEX_SERVICE_USER_HISTORY_H
#define EMOJIDEX_SERVICE_USER_HISTORY_H


#include <string>

namespace Emojidex {
	namespace Service {
		class HistoryItem {
			std::string emoji_code;
			int times_used;
			std::string last_used;
		};
	}
}

#endif /* EMOJIDEX_SERVICE_USER_HISTORY_H */
