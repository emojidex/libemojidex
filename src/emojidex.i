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
#define Init_Emojidex Init_libemojidex_ruby
%}

%import "data.i"
//%include "service.i"

//%include "client.i"

//%{
//#include "emojidex.h"
//%}

//%include "emojidex.h"
namespace Emojidex {
}
