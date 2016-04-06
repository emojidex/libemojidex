#ifndef EMOJIDEX_SERVICE_USER_HISTORY_ITEM_H
#define EMOJIDEX_SERVICE_USER_HISTORY_ITEM_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>

namespace Emojidex {
	namespace Service {
		class HistoryItem {
			public:

			std::string emoji_code;
			unsigned int times_used;
			std::string last_used;
			boost::posix_time::ptime last_used_posix;

			HistoryItem();
			HistoryItem(std::string emoji_code, unsigned int times_used, std::string last_used);
		};
	}
}

#endif /* EMOJIDEX_SERVICE_USER_HISTORY_ITEM_H */
