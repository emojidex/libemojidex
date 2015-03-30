#include "transactor.h"

#include <boost/bind.hpp>

Emojidex::Transactor::Transactor(exchange_info info_set, string api_key)
{
	this->info = info_set;
	setAPIKey(api_key);
}

void Emojidex::Transactor::setAPIKey(string api_key)
{
	this->key = api_key;
}

string Emojidex::Transactor::generateQueryString(unordered_map<string, string> *query)
{
	
	return "";
}

ssl::stream<ip::tcp::socket>* Emojidex::Transactor::getStream()
{
	io_service io_service;
	ssl::context context(io_service, ssl::context::sslv23_client);
	ssl::stream<ip::tcp::socket> *stream = new ssl::stream<ip::tcp::socket>(io_service, context);
	stream->lowest_layer().connect(
		*ip::tcp::resolver(io_service).resolve(ip::tcp::resolver::query(this->info.api_host, this->info.api_protocol))
	);
	stream->handshake(ssl::stream_base::client);

	return stream;
}

string Emojidex::Transactor::get(string endpoint, unordered_map<string, string> *query)
{
	ssl::stream<ip::tcp::socket> *stream = getStream();
	boost::asio::streambuf request;
	std::ostream request_stream(&request);

	string query_string = generateQueryString(query);
	request_stream 
		<< "GET " << this->info.api_prefix << endpoint << " HTTP/1.0\r\n"
		<< "Host: " << this->info.api_host << "\r\n"
		<< "Accept: application/json; charset=utf-8\r\n"
		<< "Connection: close" << "\r\n"
		<< "Content-Type: application/x-www-form-urlencoded; charset=UTF-8\r\n"
		<< "Content-Length: " << query_string.length() << "\r\n"
		<< "\r\n"
		<< query_string << "\r\n";
	write(*stream, request);

	boost::asio::streambuf response;
	boost::asio::read_until(*stream, response, "\r\n");

	std::istream response_stream(&response);
	std::string http_version;
	response_stream >> http_version;
	unsigned int status_code;
	response_stream >> status_code;
	string status_message;
	getline(response_stream, status_message);
	// TODO response error handling
	
	// response header
	boost::asio::read_until(*stream, response, "\r\n");
	string header;
	while (getline(response_stream, header) && header != "\r");
	// TODO handle headers line by line
	
	boost::system::error_code error;
	while (boost::asio::read(*stream, response, transfer_all(), error));
	string json_string(boost::asio::buffer_cast<const char*>(response.data()));

	// cut non-data info
	std::size_t pos = json_string.find("\r\n\r\n");
	if (pos != std::string::npos) {
		json_string = json_string.substr(pos + 4);
	}

	cout << "RESONSE: " << json_string;

	return json_string;
}
