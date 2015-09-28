#ifndef EMOJIDEX_SERVICE_USER_H
#define EMOJIDEX_SERVICE_USER_H

#include "data/collection.h"

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
				UNVERIFIED,
				VERIFIED
			};

			AuthStatusCode status;
			string username;

			User();
			~User();

			bool authorize(string username, string token);

			bool login(string user, string password);

			Emojidex::Data::Collection favorites;
			bool addFavorite(string code);
			bool removeFavorite(string code);

			Emojidex::Data::Collection history;
			unsigned int addHistory(string code);
			bool syncHistory();
		};
	}
}

#endif /* EMOJIDEX_SERVICE_USER_H */
