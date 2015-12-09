%module(package="Emojidex::Data") "Emojidex::Data::Emoji"

%nspace Emojidex::Data::Emoji;

%include <std_string.i>
%include <std_vector.i>
%include "data/checksums.i"

// For java.
SWIG_JAVABODY_PROXY(public, public, SWIGTYPE)
SWIG_JAVABODY_TYPEWRAPPER(public, public, public, SWIGTYPE)
%typemap(javaimports) Emojidex::Data::Emoji %{
import com.emojidex.libemojidex.StringVector;
%}

%{
#include "data/emoji.h"
%}

// %include "data/emoji.h"
namespace Emojidex {
  namespace Data {
    // emoji base data
    class Emoji
    {
    public:
      string moji;
      string code;
      string unicode;
      string category;
      vector<std::string> tags;
      string base;
      vector<std::string> variants;
      string link;
      // detailed
      bool is_wide;
      bool copyright_lock;
      unsigned int times_used;
      unsigned int times_favorited;
      int score;
      string attribution;
      string user_id;
      Checksums checksums;
    };
  }
}

// Rename template classes.
#ifndef TEMPLATE_STRING_VECTOR
#define TEMPLATE_STRING_VECTOR
%template(StringVector) std::vector<std::string>;
#endif
