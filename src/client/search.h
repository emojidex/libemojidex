#ifndef EMOJIDEX_SEARCH_CLIENT_H
#define EMOJIDEX_SEARCH_CLIENT_H

#include <string>

#include "comm.h"

namespace Emojidex {
	class SearchClient
	{

		public:
		unsigned int current_page;

		SearchClient();
		std::string term(std::string term);
	};
}

#endif // EMOJIDEX_SEARCH_CLIENT_H
