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

namespace Emojidex {
  // Core client class (includes all components in a central state-machine client)
  class Client
  {
  private:
    //Emojidex::Transactor *transactor;
  public:
    Emojidex::Service::Search *Search;
    Emojidex::Service::Search *Indexes;

    Client();
    char apiVersion();
  }; // Client
} // Emojidex namespace


// Include sub interface files.
// %include "service/indexes.i"

// Rename template classes.
%template(StringVector) std::vector<std::string>;
%template(EmojiVector) std::vector<Emojidex::Data::Emoji>;
