#ifndef EMOJIDEX_SERVICE_USER_H
#define EMOJIDEX_SERVICE_USER_H

#include "collector.h"
#include "user/history_item.h"

#include <vector>
#include <string>

namespace Emojidex {
	namespace Service {
		class User
		{
		private:
			// Merges a page of history items into the history list
			void mergeHistoryPage(std::vector<Emojidex::Service::HistoryItem> history_page);
			// Merges a single history item into the history list.
			// Returns true if the item was already in the history list and was updated.
			// Retruns false if the item was newly added.
			bool mergeHistoryItem(Emojidex::Service::HistoryItem history_item);
			// Sorts history list by last_used
			void sortHistory();

		public:
			enum AuthStatusCode
			{
				NONE,
				FAILURE,
				UNVERIFIED,
				VERIFIED
			};

			AuthStatusCode status;
			std::string username;
			std::string auth_token;
			bool pro;
			std::string pro_exp;
			bool premium;
			std::string premium_exp;
			bool r18;

			User();
			~User();

			bool authorize(std::string username, std::string token);

			bool login(std::string user, std::string password);

			Emojidex::Data::Collection favorites;
			bool syncFavorites(bool detailed = true);
			bool addFavorite(std::string code);
			bool removeFavorite(std::string code);

			std::vector<Emojidex::Service::HistoryItem> history;
			unsigned int history_total;
			unsigned int history_page;
			// Syncs history.
			// Consecutive calls [with page set to 0] will get the next page after history_page.
			std::vector<Emojidex::Service::HistoryItem> syncHistory(unsigned int page = 0, unsigned int limit = DEFAULT_LIMIT);
			bool addHistory(std::string code);

			// Collection of emoji the user has registered themselves
			Emojidex::Data::Collection my_emoji;
			// Sync users personal emoji
			bool syncMyEmoji();

			std::vector<std::string> following;
			bool syncFollowing();
			bool addFollowing(std::string username);
			bool removeFollowing(std::string username);

			std::vector<std::string> followers;
			bool syncFollowers();
		};
	}
}

#endif /* EMOJIDEX_SERVICE_USER_H */
