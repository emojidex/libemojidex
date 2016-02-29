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

std::string hex(unsigned int c)
{
    std::ostringstream stm ;
    stm << '%' << std::hex << std::uppercase << c ;
    return stm.str() ;
}

std::string url_encode(const std::string& str)
{
    static const std::string unreserved = "0123456789"
                                            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                            "abcdefghijklmnopqrstuvwxyz"
                                            "-_.~/" ;
    std::string result ;

    for( unsigned char c : str )
    {
        if( unreserved.find(c) != std::string::npos ) result += c ;
        else result += hex(c) ;
    }

    return result ;
}

std::string Emojidex::Service::Transactor::request(const std::string& verb, const std::string& endpoint, const std::unordered_map<string, string>& query, int* status)
{
	return this->request(verb, endpoint, generateQueryString(query), status);
}

std::string Emojidex::Service::Transactor::request(const std::string& verb, const std::string& endpoint, const std::string& query, int* status)
{
	CURL *curl;
	CURLcode res;
	string json_string = "";

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	std::stringstream url_stream;
	url_stream << Settings::api_protocol << "://" << Settings::api_host << Settings::api_prefix << url_encode(endpoint);

	if (curl) {
		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "charset: utf-8");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libemojidex/1.0");

		curl_easy_setopt(curl, CURLOPT_URL, url_stream.str().c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &json_string);
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, verb.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)query.length());

		res = curl_easy_perform(curl);
		
		if(res != CURLE_OK)
		{
			cerr << curl_easy_strerror(res);
		}

		if(status != NULL)
		{
			res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, status);
		}

		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();

	return json_string;
}

std::string Emojidex::Service::Transactor::GET(const std::string& endpoint, Emojidex::Service::QueryOpts query, int* status)
{
	return request("GET", endpoint, query.to_string(), status);
}

string Emojidex::Service::Transactor::GET(const string& endpoint, const std::unordered_map<string, string>& query, int* status)
{
	return request("GET", endpoint, query, status);
}

string Emojidex::Service::Transactor::POST(const string& endpoint, const std::unordered_map<string, string>& query, int* status)
{
	return request("POST", endpoint, query, status);
}

string Emojidex::Service::Transactor::DELETE(const string& endpoint, const std::unordered_map<string, string>& query, int* status)
{
	return request("DELETE", endpoint, query, status);
}
