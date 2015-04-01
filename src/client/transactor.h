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
using namespace boost::asio;

namespace Emojidex {
	// performs transactions with an emojidex API server
	class Transactor
	{
	private:
		std::string auth_token;

		string generateQueryString(unordered_map<string, string> query);

		ssl::stream<ip::tcp::socket>* getStream();
	public:
		typedef struct {
			string api_host;
			string api_prefix;
			string api_protocol;
			string cdn_host;
			string cdn_prefix;
			string cdn_protocol;
			bool closed_net;
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
					false
		}, string token = "");

		void setAuthToken(string token = "");

		unordered_map<string, string> queryTemplate(bool defaults = true);

		string get(string endpoint, unordered_map<string, string> query = {{"", ""}});
	};
}

#endif // EMOJIDEX_TRANSACTOR_H
