#include "transactor.h"

#include <boost/bind.hpp>
#include <boost/asio/ssl.hpp>
using namespace boost::asio;

Emojidex::Transactor::Transactor(exchange_info info_set)
{
	this->info = info_set;
}

string Emojidex::Transactor::get(string endpoint, string query)
{
	io_service io_service;
	ssl::context context(io_service, ssl::context::sslv23_client);
	ssl::stream<ip::tcp::socket> ssl_stream(io_service, context);
	ssl_stream.lowest_layer().connect(
		*ip::tcp::resolver(io_service).resolve(ip::tcp::resolver::query(this->info.api_host, this->info.api_protocol))
	);
	ssl_stream.handshake(ssl::stream_base::client);


	boost::asio::streambuf request;
	std::ostream request_stream(&request);
	request_stream 
		<< "GET " << this->info.api_prefix << endpoint << " HTTP/1.1\r\n"
		//<< "GET /api/v1/popular HTTP/1.1\r\n"
		<< "Host: " << this->info.api_host << "\r\n"
		<< "Content-Length: " << query.length() << "\r\n"
		<< "Connection: Close" << "\r\n"
		<< "\r\n"
		<< query << "\r\n";
	write(ssl_stream, request);

	boost::asio::streambuf response;
	boost::asio::read_until(ssl_stream, response, "\r\n");

	std::istream response_stream(&response);
	std::string http_version;
	response_stream >> http_version;
	unsigned int status_code;
	response_stream >> status_code;

	string *json_string = new string("");
	boost::system::error_code error;
	while(boost::asio::read(ssl_stream, response, transfer_at_least(1), error))
		*json_string = boost::asio::buffer_cast<const char*>(response.data());

	std::size_t pos = json_string->find("\r\n\r\n");
	if (pos != std::string::npos) {
		*json_string = json_string->substr(pos + 4);
	}

	cout << "RESONSE: " << *json_string;

	return *json_string;
}
