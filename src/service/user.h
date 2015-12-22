#ifndef EMOJIDEX_SERVICE_USER_H
#define EMOJIDEX_SERVICE_USER_H

#include "collector.h"
#include "user/history.h"

#include <string>

namespace Emojidex {
	namespace Service {
		class User
		{
		private:
			std::string token;

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
			bool pro;
			std::string pro_exp;
			bool premium;
			std::string premium_exp;
			bool r18;
			// WARNING: debug
			std::string response;

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
			std::vector<Emojidex::Service::HistoryItem> syncHistory(unsigned int limit = Emojidex::Service::Collector::DefaultLimit, unsigned int page = 0, bool detailed = false);
			unsigned int addHistory(std::string code);
		};
	}
}

#endif /* EMOJIDEX_SERVICE_USER_H */
