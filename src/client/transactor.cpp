#include "transactor.h"
#include <sstream>

Emojidex::Transactor::Transactor(exchange_info info_set)
{
	this->info = info_set;
	//curl_easy easy;
  //  try {
  //      easy.add(curl_pair<CURLoption,string>(CURLOPT_URL,"http://example.com"));
  //      // Just connect
  //      easy.add(curl_pair<CURLoption,bool>(CURLOPT_CONNECT_ONLY,true));
  //      easy.perform();
  //  } catch (curl_easy_exception error) {
  //      // If you want to get the entire error stack we can do:
  //      vector<pair<string,string>> errors = error.what();
  //      // Print errors if any
  //      error.print_traceback();
  //  }
}

string Emojidex::Transactor::get(string endpoint, string opts)
{
	stringstream url;
	url << info.api_protocol << "://" << info.api_url << endpoint;
	curl_writer writer;
	curl_easy easy(writer);
	easy.add(curl_pair<CURLoption, string>(CURLOPT_URL, url.str()));
	try {
		easy.perform();
	} catch (curl_easy_exception error) {
		vector<pair<string,string>> errors = error.what();
        error.print_traceback();
		return "";
	}

	stringstream ss;
	ss << writer.get_stream();
	return ss.str();
}
