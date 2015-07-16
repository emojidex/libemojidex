%module(package="Emojidex::Service") "Emojidex::Service::Search"

%nspace Emojidex::Service::Search;

%include <std_string.i>

%{
#include "service/search.h"
%}

namespace Emojidex {
  namespace Service {
    class Search
    {
    public:
      unsigned int current_page;

      Search();
      Emojidex::Data::Collection term(std::string term);
    };
  }
}
