%module Emojidex_Service_Search

%{
include "search.h"
%}

namespace Emojidex {
  namespace Service {
    class Search
    {
    public:
      unsigned int current_page;

      Search();
      Emojidex::Data::Collection term(string term);
    };
  }
}
