%module(package="Emojidex::Data") "Emojidex::Data::Checksums"


%{
#include "data/checksums.h"
%}

%include <std_string.i>

// %include "data/checksums.h"
namespace Emojidex {
  namespace Data {
    class Checksums
    {
    public:
      std::string sum(std::string format_code, std::string size_code);
    };
  }
}
