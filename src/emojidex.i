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

%include "./data.i"

//%include "./client.i"
//%include "./service/indexes.i"
//%include "./service/search.i"

%include "emojidex.h"

%template(StringVector) std::vector<std::string>;
%template(EmojiVector) std::vector<Emojidex::Data::Emoji>;
