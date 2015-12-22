%module(package="Emojidex::Data") "Emojidex::Data::Checksums"

%nspace Emojidex::Data::Checksums;

%include <std_string.i>

%{
#include "data/checksums.h"
%}

// %include "data/checksums.h"
namespace Emojidex {
  namespace Data {
    class Checksums
    {
    public:
      std::string svg;
//      std::unordered_map <std::string, std::string> png;

      std::string sum(std::string format_code, std::string size_code);
    };
  }
}
