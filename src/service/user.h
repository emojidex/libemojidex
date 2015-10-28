#ifndef EMOJIDEX_SERVICE_USER_H
#define EMOJIDEX_SERVICE_USER_H

#include "collector.h"
using namespace Emojidex::Service;
using namespace Emojidex::Data;

#include <string>
using namespace std;

namespace Emojidex {
	namespace Service {
		class User
		{
		private:
			string token;

		public:
			enum AuthStatusCode
			{
				NONE,
				FAILURE,
				UNVERIFIED,
				VERIFIED
			};

			AuthStatusCode status;
			string username;
			bool pro;
			bool premium;
			// WARNING: debug
			string response;

			User();
			~User();

			bool authorize(string username, string token);

			bool login(string user, string password);

			Collection favorites;
			bool syncFavorites(bool detailed = true);
			bool addFavorite(string code);
			bool removeFavorite(string code);

			Collection history;
			Collection syncHistory(unsigned int limit = Collector::DefaultLimit, bool detailed = false);
			unsigned int addHistory(string code);
		};
	}
}

#endif /* EMOJIDEX_SERVICE_USER_H */
