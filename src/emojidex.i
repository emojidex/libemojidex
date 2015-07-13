%module Emojidex

// For java.
%pragma(java) jniclasscode=%{
  static
  {
    NativeLibLoader.load();
  }
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
