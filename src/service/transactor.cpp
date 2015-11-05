#include "transactor.h"

#include "./settings.h"

#include <iostream>
#include <boost/bind.hpp>

#include <curl/curl.h>

using namespace std;

namespace
{
	size_t writeMemoryCallback(char *ptr, size_t size, size_t nmemb, void *userdata)
	{
		const size_t realsize = size * nmemb;
		((string*)userdata)->append(ptr, realsize);
		return realsize;
	}
}

Emojidex::Service::Transactor::Transactor()
{
}

std::unordered_map<string, string> Emojidex::Service::Transactor::queryTemplate(bool defaults)
{
	std::unordered_map<string, string> q;

	if (defaults) {
		if (Settings::token != "")
			q["auth_token"] = Settings::token;
	}

	return q;
}

string Emojidex::Service::Transactor::generateQueryString(std::unordered_map<string, string> query)
{
	stringstream query_ss;

	for (auto q : query)
		if (q.first != "" && q.second != "")
			query_ss << q.first << "=" << q.second << "&";

	string query_s = query_ss.str();
	return query_s.substr(0, query_s.size() - 1);
}

boost::asio::ssl::stream<boost::asio::ip::tcp::socket>* Emojidex::Service::Transactor::getStream()
{
	boost::asio::io_service io_service;
	boost::asio::ssl::context context(io_service, boost::asio::ssl::context::sslv23_client);
	boost::asio::ssl::stream<boost::asio::ip::tcp::socket> *stream = new boost::asio::ssl::stream<boost::asio::ip::tcp::socket>(io_service, context);
	stream->lowest_layer().connect(
		*boost::asio::ip::tcp::resolver(io_service).resolve(boost::asio::ip::tcp::resolver::query(Settings::api_host, Settings::api_protocol))
	);
	stream->handshake(boost::asio::ssl::stream_base::client);

	return stream;
}

string Emojidex::Service::Transactor::get(string endpoint, std::unordered_map<string, string> query, string* url)
{
	CURL *curl;
	CURLcode res;
	string json_string = "";

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	
	stringstream url_stream;
	url_stream << Settings::api_protocol << "://" << Settings::api_host << Settings::api_prefix << endpoint << "?" << generateQueryString(query);
	if(url != NULL)
		*url = url_stream.str();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url_stream.str().c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &json_string);

		res = curl_easy_perform(curl);
		
		if(res != CURLE_OK)
		{
			cerr << curl_easy_strerror(res);
			json_string.clear();
		}
		
		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();

	return json_string;
}
