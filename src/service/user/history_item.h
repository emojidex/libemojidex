#ifndef EMOJIDEX_SERVICE_USER_HISTORY_ITEM_H
#define EMOJIDEX_SERVICE_USER_HISTORY_ITEM_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>

namespace Emojidex {
	namespace Service {
		//! Container for entries in a users history
		class HistoryItem {
			public:

			//! The code of the emoji used
			std::string emoji_code;
			//! The number of times the user has used this emoji
			unsigned int times_used;
			//! String noting the last time the emoji was used 
			std::string last_used;
			//! POSIX time object with the last time the emoji was used
			boost::posix_time::ptime last_used_posix;

			HistoryItem();
			//! Quickly initialize a filled HistoryItem object
			HistoryItem(std::string emoji_code, unsigned int times_used, std::string last_used);
		};
	}
}

#endif /* EMOJIDEX_SERVICE_USER_HISTORY_ITEM_H */
