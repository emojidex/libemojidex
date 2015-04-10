%module libemojidex

%pragma(java) jniclasscode=%{
  static
  {
    NativeLibLoader.load();
  }
%}

%{
#include "client.h"
%}

%include "client.h"
