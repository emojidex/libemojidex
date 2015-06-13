%module Emojidex

%include "./data/emoji.i"
%include "./data/collection.i"

%include "./client.i"
%include "./service/indexes.i"
%include "./service/search.i"

%{
#include "emojidex.h"
%}

namespace Emojidex {
}
