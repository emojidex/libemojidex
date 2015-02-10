#ifndef EMOJIDEX_TRANSACTOR_H
#define EMOJIDEX_TRANSACTOR_H

#include <curl/curl.h>
#include <string>
#include <iostream>
using namespace std;

#include "curl_easy.h"
#include "curl_writer.h"
using curl::curl_easy;

namespace Emojidex {
	// performs transactions with an emojidex API server
	class Transactor
	{
	private:
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
