#ifndef EMOJIDEX_TRANSACTOR_H
#define EMOJIDEX_TRANSACTOR_H

#include <string>
#include <iostream>
#include <istream>
#include <ostream>
#include <unordered_map>
using namespace std;
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "./settings.h"
using namespace Emojidex::Service;

namespace Emojidex {
	namespace Service {
		// performs transactions with an emojidex API server
		class Transactor
		{
		private:
			string generateQueryString(unordered_map<string, string> query);
			boost::asio::ssl::stream<boost::asio::ip::tcp::socket>* getStream();
		public:
			Transactor();

			unordered_map<string, string> queryTemplate(bool defaults = true);

			string get(string endpoint, unordered_map<string, string> query = {{"", ""}});
		};
	}
}

#endif // EMOJIDEX_TRANSACTOR_H
