#ifndef EMOJIDEX_COMM_H
#define EMOJIDEX_COMM_H

#include <string>
#include <iostream>
using namespace std;

#include <boost/asio.hpp>
namespace asio = boost::asio;
namespace ip = asio::ip;

namespace Emojidex {
	typedef struct {
		string api_url	{"www.emojidex.com/api/v1/"};
		string api_protocol {"https"};
		string cdn_url	{"cdn.emojidex.com/"};
		string cdn_protocol {"http"};
		string locale	{"en"};
		bool closed_net {false};
		unsigned int limit {512};
	} comm_info;

	class Comm
	{
		private:
		ip::tcp::socket *sock;
		ip::tcp::resolver *resolver;
		ip::tcp::resolver::query *query;

		public:
		comm_info info;

		Comm();
		Comm(comm_info info);

	};
}

#endif // EMOJIDEX_COMM_H
