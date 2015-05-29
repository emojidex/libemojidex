%module emojidex

// Include STL header files.
%include "std_string.i"
%include "std_vector.i"

// For java.
%pragma(java) jniclasscode=%{
  static
  {
    NativeLibLoader.load();
  }
%}

// 
%{
#include "client.h"
%}

// Include sub interfaces.
%include "version.i"
%include "service/indexes.i"

// Rename template classes.
%template(StringVector) std::vector<std::string>;
%template(EmojiVector) std::vector<Emojidex::Data::Emoji>;
