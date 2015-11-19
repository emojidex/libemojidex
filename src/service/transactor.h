#ifndef EMOJIDEX_TRANSACTOR_H
#define EMOJIDEX_TRANSACTOR_H

#include <string>
#include <unordered_map>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>


namespace Emojidex {
	namespace Service {
		// performs transactions with an emojidex API server
		class Transactor
		{
		private:
			std::string generateQueryString(std::unordered_map<std::string, std::string> query);
			boost::asio::ssl::stream<boost::asio::ip::tcp::socket>* getStream();
		public:
			Transactor();

			std::unordered_map<std::string, std::string> queryTemplate(bool defaults = true);

			std::string get(std::string endpoint, std::unordered_map<std::string, std::string> query = {{"", ""}}, std::string* url = NULL);
			std::string post(std::string endpoint, std::unordered_map<std::string, std::string> query = {{"", ""}}, std::string* url = NULL);
			std::string delete_(std::string endpoint, std::unordered_map<std::string, std::string> query = {{"", ""}}, std::string* url = NULL);
		};
	}
}

#endif // EMOJIDEX_TRANSACTOR_H
