#ifndef EMOJIDEX_TRANSACTOR_H
#define EMOJIDEX_TRANSACTOR_H

#include <string>
#include <unordered_map>

#define TF(bv) ((bv)?"true":"false")

namespace Emojidex {
	namespace Service {
		// performs transactions with an emojidex API server
		class Transactor
		{
		private:
			std::string generateQueryString(const std::unordered_map<std::string, std::string>& query);
			std::string request(const std::string& requestname, const std::string& endpoint, const std::unordered_map<std::string, std::string>& query, int* status);
		public:
			Transactor();

			std::unordered_map<std::string, std::string> queryTemplate(bool defaults = true);

			std::string GET(const std::string& endpoint, const std::unordered_map<std::string, std::string>& query = {{"", ""}}, int* status = NULL);
			std::string POST(const std::string& endpoint, const std::unordered_map<std::string, std::string>& query = {{"", ""}}, int* status = NULL);
			std::string DELETE(const std::string& endpoint, const std::unordered_map<std::string, std::string>& query = {{"", ""}}, int* status = NULL);
		};
	}
}

#endif // EMOJIDEX_TRANSACTOR_H
