#include "transactor.h"

#include <boost/bind.hpp>

Emojidex::Service::Transactor::Transactor(exchange_info info_set, string token)
{
	this->info = info_set;
	setAuthToken(token);
}

void Emojidex::Service::Transactor::setAuthToken(string token)
{
	this->auth_token = token;
}

unordered_map<string, string> Emojidex::Service::Transactor::queryTemplate(bool defaults)
{
	unordered_map<string, string> q;

	if (defaults) {
		if (this->auth_token != "")
			q["auth_token"] = this->auth_token;
	}

	return q;
}

string Emojidex::Service::Transactor::generateQueryString(unordered_map<string, string> query)
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
		*boost::asio::ip::tcp::resolver(io_service).resolve(boost::asio::ip::tcp::resolver::query(this->info.api_host, this->info.api_protocol))
	);
	stream->handshake(boost::asio::ssl::stream_base::client);

	return stream;
}

string Emojidex::Service::Transactor::get(string endpoint, unordered_map<string, string> query)
{
	// TODO clean this the fuck up
	boost::asio::ssl::stream<boost::asio::ip::tcp::socket> *stream = getStream();
	boost::asio::streambuf request;
	std::ostream request_stream(&request);

	string query_string = generateQueryString(query);
	/* TODO HTTP 1.1+ (chunking etc.) */
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
	if (status_code < 200 || status_code >= 300) {
		cerr << "[" << status_code << "]:" << status_message << endl;
		return "";
	}

	// response header
	boost::asio::read_until(*stream, response, "\r\n");
	string header;
	while (getline(response_stream, header) && header != "\r");
	// TODO handle headers line by line
	
	boost::system::error_code error;
	while (boost::asio::read(*stream, response, boost::asio::transfer_all(), error));
	string json_string(boost::asio::buffer_cast<const char*>(response.data()));

	// cut non-data info
	std::size_t pos = json_string.find("\r\n\r\n");
	if (pos != std::string::npos) {
		json_string = json_string.substr(pos + 4);
	}

	return json_string;
}
