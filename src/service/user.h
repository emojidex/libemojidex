#ifndef EMOJIDEX_SERVICE_USER_H
#define EMOJIDEX_SERVICE_USER_H

#include "collector.h"
#include "user/history_item.h"

#include <vector>
#include <string>

namespace Emojidex {
	namespace Service {
		//! User login/management for the emojidex service
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
			//! Status codes denoting the current authorization/login status of the user
			enum AuthStatusCode
			{
				NONE,
				FAILURE,
				UNVERIFIED,
				VERIFIED
			};

			//! Holds the current status for this user instance (defaults to NONE)
			AuthStatusCode status;
			//! User name of the user (defaults to "")
			std::string username;
			//! Authorization token of the user (defaults to "")
			std::string auth_token;
			//! True if the user has an active Pro account
			bool pro;
			//! Ending date of Pro status (blank if user was never Pro)
			std::string pro_exp;
			//! True if the user has an active Premium account
			bool premium;
			//! Ending date of Premium status (blank if user was never Premium)
			std::string premium_exp;
			//! True if the user has enabled viewing r18 [adult] content
			bool r18;

			User();
			~User();

			//! Authroize the user with a username and auth_token
			bool authorize(std::string username, std::string token);

			//! Authroize a user with a username or e-mail and password
			bool login(std::string user, std::string password);

			//! A collection of the emoji the user has favorited
			Emojidex::Data::Collection favorites;
			//! Synchronize user favorites from the emojidex service
			/*!
			 * Synchronizing clears the favorites collection and obtains the
			 * first page of favorites. Call favorites.more() to retreive 
			 * consecutive pages.
			 */
			bool syncFavorites(bool detailed = true);
			//! Register an emoji to users favorites on the emojidex service
			bool addFavorite(std::string code);
			//! Remove an emoji from users favorites on the emojidex service
			bool removeFavorite(std::string code);

			//! An ordered vector of items in the users history
			std::vector<Emojidex::Service::HistoryItem> history;
			//! Total number of history items stored on the emojidex service
			unsigned int history_total;
			//! Current page of history items taken from the emojidex service
			unsigned int history_page;
			//! Syncronize history from the emojidex service
			/*!
			 * Consecutive calls [with page set to 0] will get the next page after history_page.
			 * The last page of history obtained is returned.
			 */
			std::vector<Emojidex::Service::HistoryItem> syncHistory(unsigned int page = 0, unsigned int limit = DEFAULT_LIMIT);
			//! Add an emoji to the users history
			bool addHistory(std::string code);

			//! Collection of emoji the user has registered themselves
			Emojidex::Data::Collection my_emoji;
			//! Sync users personal emoji
			/*!
			 * Synchronizing clears the my_emoji collection.
			 * After sycronizing call my_collection.more() to obtain consecutive pages of user emoji.
			 */
			bool syncMyEmoji();

			//! List of users the user is following
			std::vector<std::string> following;
			//! Synchronizes the users following list
			bool syncFollowing();
			//! Adds a user to the following list
			bool addFollowing(std::string username);
			//! Removes a user from the following list
			bool removeFollowing(std::string username);

			//! List of people following this user (Premium/Pro only)
			std::vector<std::string> followers;
			//! Synchronizes followers from the emojidex service (Premium/Pro only)
			bool syncFollowers();
		};
	}
}

#endif /* EMOJIDEX_SERVICE_USER_H */
