#ifndef EMOJIDEX_SEARCH_CLIENT_H
#define EMOJIDEX_SEARCH_CLIENT_H

#include "transactor.h"
#include "../emoji.h"

#include <string>
#include <vector>
using namespace std;

namespace Emojidex {
	class SearchClient
	{
	public:
		unsigned int current_page;

		SearchClient();
		vector<Emojidex::Emoji> term(string term);
	};
}

#endif // EMOJIDEX_SEARCH_CLIENT_H
