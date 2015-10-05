%module LibEmojidex

// For java.
%pragma(java) jniclasscode=%{
  static
  {
    NativeLibLoader.load();
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
