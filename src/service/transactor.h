#ifndef EMOJIDEX_TRANSACTOR_H
#define EMOJIDEX_TRANSACTOR_H

#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "../data/unordered_map.h"

namespace Emojidex {
	namespace Service {
		// performs transactions with an emojidex API server
		class Transactor
		{
		private:
			std::string generateQueryString(Data::UnorderedMap<std::string, std::string> query);
			boost::asio::ssl::stream<boost::asio::ip::tcp::socket>* getStream();
		public:
			Transactor();

			Data::UnorderedMap<std::string, std::string> queryTemplate(bool defaults = true);

			std::string get(std::string endpoint, Data::UnorderedMap<std::string, std::string> query = {{"", ""}});
		};
	}
}

#endif // EMOJIDEX_TRANSACTOR_H
