%module "Emojidex::Data::Checksums"

%include "std_string.i"
%ignore Emojidex::Data::Checksums::png;

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
      Data::UnorderedMap <std::string, std::string> png;

      std::string sum(std::string format_code, std::string size_code);
    };
  }
}
