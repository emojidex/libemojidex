#ifndef _EMOJIDEX_CLIENT_SEARCH_H_
#define _EMOJIDEX_CLIENT_SEARCH_H_

#include <string>

namespace Emojidex {
	class SearchClient
	{
		public:
		SearchClient();
		std::string term(std::string term);
	};
}

#endif // _EMOJIDEX_CLIENT_SEARCH_H_
