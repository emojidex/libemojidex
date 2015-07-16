%module Emojidex

// For java.
%pragma(java) jniclasscode=%{
  static
  {
    NativeLibLoader.load();
  }
%}

// For ruby.
%{
#ifdef SWIGRUBY
#define Init_Emojidex Init_libemojidex_ruby
#endif
%}

%include "client.i"
%include "data.i"
%include "service.i"
