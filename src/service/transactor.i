%module(package="Emojidex::Service") "Emojidex::Service::Transactor"

%nspace Emojidex::Service::Transactor;

%include <std_string.i>

%{
include "service/transactor.h"
%}

// Ignore unordered_map.
%ignore Emojidex::Service::Transactor::queryTemplate;
%ignore Emojidex::Service::Transactor::get;

// %include "service/transactor.h"
namespace Emojidex {
  namespace Service {
    // performs transactions with an emojidex API server
    class Transactor
    {
    private:
      std::string generateQueryString(const std::unordered_map<std::string, std::string>& query);
      boost::asio::ssl::stream<boost::asio::ip::tcp::socket>* getStream();
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
