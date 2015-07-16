%module(package="Emojidex") "Emojidex::Data"

%{
#include "data.h"
%}

%include "data/emoji.i"
%include "data/collection.i"
%include "data/checksums.i"
%include "data/moji_codes.i"
