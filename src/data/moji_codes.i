%module DataMojiCodes

%include "std_string.i"
%include "std_vector.i"
//%include "std_unordered_map.i"

%{
include "moji_codes.h"
%}

namespace Emojidex {
  namespace Data {
    // Moji code container with 3 types of moji code indexes
    class MojiCodes
    {
    public:
      string locale = "";
      string moji_string;
      vector<string> moji_array;
      unordered_map<string, string> moji_index;
    };
  }
}
