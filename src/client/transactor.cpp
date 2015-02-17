#include "transactor.h"

Emojidex::Transactor::Transactor(exchange_info info_set)
{
	this->info = info_set;
}

string Emojidex::Transactor::get(string path, string opts)
{
	io_service io_service; // service handle
	ip::tcp::socket sock(io_service); // create a socket

	// resolve IP address from URL
	ip::tcp::resolver resolver(io_service);
	ip::tcp::resolver::query query(this->info.api_url, this->info.api_protocol);

	// set the resolved endpoint
	ip::tcp::endpoint endpoint(*resolver.resolve(query));

	sock.connect(endpoint); // connect to endpoint through socket

	boost::asio::streambuf request;
	ostream request_ostream(&request);
	request_ostream << "GET " << this->info.api_prefix << path << " HTTP/1.1\r\n\r\n";
	write(sock, request);

	boost::asio::streambuf response_buffer;
	boost::system::error_code error;
	boost::asio::read(sock, response_buffer, boost::asio::transfer_all(), error);
	if (error && error != boost::asio::error::eof)
		return error.message();

	cout << "response" << &response_buffer; //debug TODO remove
	istream is(&response_buffer);
	string response_string;
	is >> response_string;
	return response_string;
}
