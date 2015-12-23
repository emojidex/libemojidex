#include "transactor.h"
#include "settings.h"

#include <curl/curl.h>

#include <sstream>
#include <iostream>
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

string Emojidex::Service::Transactor::generateQueryString(const std::unordered_map<string, string>& query)
{
	std::stringstream query_ss;

	for (auto q : query)
		if (q.first != "" && q.second != "")
			query_ss << q.first << "=" << q.second << "&";

	string query_s = query_ss.str();
	return query_s.substr(0, query_s.size() - 1);
}

std::string Emojidex::Service::Transactor::request(const std::string& requestname, const std::string& endpoint, const std::unordered_map<string, string>& query, std::string* url)
{
	CURL *curl;
	CURLcode res;
	string json_string = "";

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	std::stringstream url_stream;
	url_stream << Settings::api_protocol << "://" << Settings::api_host << Settings::api_prefix << endpoint;
	if(url != NULL)
		*url = url_stream.str();

	if (curl) {
		const string query_string = generateQueryString(query);
		curl_easy_setopt(curl, CURLOPT_URL, url_stream.str().c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &json_string);
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, requestname.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query_string.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)query_string.length());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);

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

string Emojidex::Service::Transactor::get(const string& endpoint, const std::unordered_map<string, string>& query, string* url)
{
	return request("GET", endpoint, query, url);
}

string Emojidex::Service::Transactor::post(const string& endpoint, const std::unordered_map<string, string>& query, string* url)
{
	return request("POST", endpoint, query, url);
}

string Emojidex::Service::Transactor::del(const string& endpoint, const std::unordered_map<string, string>& query, string* url)
{
	return request("DELETE", endpoint, query, url);
}
