%module libemojidex

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

// Ignore function pointer.
%ignore Emojidex::Data::Collection::moreMethod;
%ignore Emojidex::Data::Collection::setPagination;

// Ignore operator.
%ignore Emojidex::Data::Collection::operator<<;

// Ignore unordered_map.
%ignore Emojidex::Data::Collection::emoji;
%ignore Emojidex::Data::MojiCodes::moji_index;
%ignore Emojidex::Service::Transactor::queryTemplate;
%ignore Emojidex::Service::Transactor::get;

// Include header files.
%include "client.h"
%include "data/emoji.h"
%include "data/collection.h"
%include "data/moji_codes.h"
%include "service/indexes.h"
%include "service/search.h"
%include "service/settings.h"
%include "service/transactor.h"

// Rename template classes.
%template(StringVector) std::vector<std::string>;
%template(EmojiVector) std::vector<Emojidex::Data::Emoji>;
