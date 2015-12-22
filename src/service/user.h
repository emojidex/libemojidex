#ifndef EMOJIDEX_SERVICE_USER_H
#define EMOJIDEX_SERVICE_USER_H

#include "collector.h"

#include <string>
// using namespace std;

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
			bool premium;
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

			Emojidex::Data::Collection history;
			Emojidex::Data::Collection syncHistory(unsigned int limit = Emojidex::Service::Collector::DefaultLimit, bool detailed = false);
			unsigned int addHistory(std::string code);
		};
	}
}

#endif /* EMOJIDEX_SERVICE_USER_H */
