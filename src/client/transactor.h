#ifndef EMOJIDEX_TRANSACTOR_H
#define EMOJIDEX_TRANSACTOR_H

#include <string>
#include <iostream>
#include <istream>
#include <ostream>
using namespace std;
#include <boost/asio.hpp>
#include <boost/bind.hpp>
using boost::asio::ip::tcp;

namespace Emojidex {
	// performs transactions with an emojidex API server
	class Transactor
	{
	private:
		tcp::resolver resolver
	public:
		typedef struct {
			string api_url;
			string api_protocol;
			string cdn_url;
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
		string api_addr;

		Transactor(exchange_info info_set = {"www.emojidex.com/api/v1/",
					"https",
					"cdn.emojidex.com/",
					"http",
					"en",
					false,
					512
		});

		string get(string url, string opts = "");
	};
}

#endif // EMOJIDEX_TRANSACTOR_H
