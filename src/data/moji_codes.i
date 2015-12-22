%module(package="Emjidex::Data") "Emojidex::Data::MojiCodes"

%nspace Emojidex::Data::MojiCodes;

%include <std_string.i>
%include <std_vector.i>

// For java.
SWIG_JAVABODY_PROXY(public, public, SWIGTYPE)
SWIG_JAVABODY_TYPEWRAPPER(public, public, public, SWIGTYPE)
%typemap(javaimports) Emojidex::Data::MojiCodes %{
import com.emojidex.libemojidex.StringVector;
%}

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
      std::unordered_map<std::string, std::string> moji_index;
    };
  }
}

// Rename template classes.
#ifndef TEMPLATE_STRING_VECTOR
#define TEMPLATE_STRING_VECTOR
%template(StringVector) std::vector<std::string>;
#endif

