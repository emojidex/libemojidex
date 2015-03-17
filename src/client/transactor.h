#ifndef EMOJIDEX_TRANSACTOR_H
#define EMOJIDEX_TRANSACTOR_H

#include <string>
#include <iostream>
#include <istream>
#include <ostream>
using namespace std;
#include <boost/asio.hpp>
using namespace boost::asio;

namespace Emojidex {
	// performs transactions with an emojidex API server
	class Transactor
	{
	private:
	public:
		typedef struct {
			string api_host;
			string api_prefix;
			string api_protocol;
			string cdn_host;
			string cdn_prefix;
			string cdn_protocol;
			string locale;
			bool closed_net;
			unsigned int limit;
		} exchange_info;

		typedef struct {
			string key;
			string value;
		} opt;

		exchange_info info;

		Transactor(exchange_info info_set = {"www.emojidex.com",
					"/api/v1/",
					"https",
					"cdn.emojidex.com",
					"/emoji/",
					"http",
					"en",
					false,
					512
		});

		string get(string path, string query = "");
	};
}

#endif // EMOJIDEX_TRANSACTOR_H
