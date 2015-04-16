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
%include "data/emoji.h"
%include "data/collection.h"
%include "data/moji_codes.h"
%include "service/indexes.h"
%include "service/search.h"
%include "service/transactor.h"
