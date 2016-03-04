%module LibEmojidex

// For java.
%pragma(java) jniclasscode=%{
  static
  {
    LibemojidexInitializer.initialize();
  }
%}

// For ruby.
#ifdef SWIGRUBY
%{
#define Init_LibEmojidex Init_libemojidex_ruby
%}
#endif

%include "client.i"
%include "data.i"
%include "service.i"

namespace Emojidex {
  void setCACertPath(const std::string &path = "");
  const std::string& getCACertPath(void);
}
