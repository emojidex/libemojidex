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
  //! Set the path to the CA certificate for SSL
  void setCACertPath(const std::string &path = "");
  //! Get the [current/system] path to the CA certificate
  const std::string& getCACertPath(void);
}
