#ifndef EMOJIDEX_TRANSACTOR_H
#define EMOJIDEX_TRANSACTOR_H

#include <string>
#include <unordered_map>
#include "./query_opts.h"

namespace Emojidex {
	namespace Service {
		//! performs transactions with an emojidex API server
		class Transactor
		{
		private:
			std::string generateQueryString(const std::unordered_map<std::string, std::string>& query);
			std::string request(const std::string& requestname, const std::string& endpoint, const std::unordered_map<std::string, std::string>& query, int* status, bool msgpack);
			std::string request(const std::string& requestname, const std::string& endpoint, const std::string& query, int* status, bool msgpack);
		public:
			Transactor();

			//! Get a blanked query hash instance
			std::unordered_map<std::string, std::string> queryTemplate(bool defaults = true);

			//! HTTP(S) Get with a query hash
			std::string GET(const std::string& endpoint, const std::unordered_map<std::string, std::string>& query = {{"", ""}}, int* status = NULL, bool msgpack = true);
			//! HTTP(S) Get with a QueryOpts instance
			std::string GET(const std::string& endpoint, Emojidex::Service::QueryOpts query, int* status = NULL, bool msgpack = true);
			//! Post with a query hash
			std::string POST(const std::string& endpoint, const std::unordered_map<std::string, std::string>& query = {{"", ""}}, int* status = NULL, bool msgpack = true);
			//! Delete with a query hash
			std::string DELETE(const std::string& endpoint, const std::unordered_map<std::string, std::string>& query = {{"", ""}}, int* status = NULL, bool msgpack = true);
		};
	}
}

#endif // EMOJIDEX_TRANSACTOR_H
