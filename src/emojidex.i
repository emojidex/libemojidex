%module Emojidex

// For java.
%pragma(java) jniclasscode=%{
  static
  {
    NativeLibLoader.load();
  }
%}

// Rename template classes.

// pre-declare common standard inclusions
%include "std_string.i"
%include "std_vector.i"

%include "data.i"
%include "service.i"

%{
#include "emojidex.h"
%}

//%include "emojidex.h"
namespace Emojidex {
}

//%template(StringVector) std::vector<std::string>;
//%template(EmojiVector) std::vector<Emojidex::Data::Emoji>;
