#ifndef EMOJIDEX_SERVICE_SEARCH_H
#define EMOJIDEX_SERVICE_SEARCH_H

#include "transactor.h"
#include "../emoji.h"

#include <string>
#include <vector>
using namespace std;

namespace Emojidex {
	namespace Service {
		class Search
		{
		public:
			unsigned int current_page;

			Search();
			vector<Emojidex::Emoji> term(string term);
		};
	}
}

#endif /* EMOJIDEX_SERVICE_SEARCH_H */
