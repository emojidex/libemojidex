%module "Emojidex::Service::Transactor"

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
      std::string generateQueryString(Data::UnorderedMap<std::string, std::string> query);
      boost::asio::ssl::stream<boost::asio::ip::tcp::socket>* getStream();
    public:
      Transactor();

      Data::UnorderedMap<std::string, std::string> queryTemplate(bool defaults = true);

      std::string get(std::string endpoint, Data::UnorderedMap<std::string, std::string> query = {{"", ""}});
    };
  }
}
