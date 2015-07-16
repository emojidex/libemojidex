%module(package="Emjidex::Data") "Emojidex::Data::MojiCodes"

%nspace Emojidex::Data::MojiCodes;

%include <std_string.i>
%include <std_vector.i>

%{
#include "data/moji_codes.h"
%}

// Ignore unoredered_map.
%ignore Emojidex::Data::MojiCodes::moji_index;

// %include "data/moji_codes.h"
namespace Emojidex {
  namespace Data {
    // Moji code container with 3 types of moji code indexes
    class MojiCodes
    {
    public:
      std::string locale = "";
      std::string moji_string;
      std::vector<std::string> moji_array;
      Data::UnorderedMap<std::string, std::string> moji_index;
    };
  }
}

// Rename template classes.
%template(StringVector) std::vector<std::string>;
