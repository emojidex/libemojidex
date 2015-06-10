%module ServiceTransactor

%{
include "service/transactor.h"
%}

namespace Emojidex {
  namespace Service {
    // performs transactions with an emojidex API server
    class Transactor
    {
    private:
      string generateQueryString(unordered_map<string, string> query);
      boost::asio::ssl::stream<boost::asio::ip::tcp::socket>* getStream();
    public:
      Transactor();

      unordered_map<string, string> queryTemplate(bool defaults = true);

      string get(string endpoint, unordered_map<string, string> query = {{"", ""}});
    };
  }
}
