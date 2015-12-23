#ifndef EMOJIDEX_TRANSACTOR_H
#define EMOJIDEX_TRANSACTOR_H

#include <string>
#include <unordered_map>

namespace Emojidex {
	namespace Service {
		// performs transactions with an emojidex API server
		class Transactor
		{
		private:
			std::string generateQueryString(const std::unordered_map<std::string, std::string>& query);
			std::string request(const std::string& requestname, const std::string& endpoint, const std::unordered_map<std::string, std::string>& query, std::string* url);
		public:
			Transactor();

			std::unordered_map<std::string, std::string> queryTemplate(bool defaults = true);

			std::string get(const std::string& endpoint, const std::unordered_map<std::string, std::string>& query = {{"", ""}}, std::string* url = NULL);
			std::string post(const std::string& endpoint, const std::unordered_map<std::string, std::string>& query = {{"", ""}}, std::string* url = NULL);
			std::string del(const std::string& endpoint, const std::unordered_map<std::string, std::string>& query = {{"", ""}}, std::string* url = NULL);
		};
	}
}

#endif // EMOJIDEX_TRANSACTOR_H
