#ifndef EMOJIDEX_TRANSACTOR_H
#define EMOJIDEX_TRANSACTOR_H

#include <curl/curl.h>
#include <string>
using namespace std;

#include "curl_easy.h"
using curl::curl_easy;

namespace Emojidex {
	// performs transactions with an emojidex API server
	class Transactor
	{
	private:
		curl_easy *easy;
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

		exchange_info info;

		Transactor(exchange_info info_set = {"www.emojidex.com/api/v1/",
					"https",
					"cdn.emojidex.com/",
					"http",
					"en",
					false,
					512
		});
	};
}

#endif // EMOJIDEX_TRANSACTOR_H
