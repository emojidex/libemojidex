%module(package="Emojidex::Data") "Emojidex::Data::Checksums"

%nspace Emojidex::Data::Checksums;

%include <std_string.i>
%include "unordered_map_string_string.i"

%{
#include "data/checksums.h"
%}

%include "data/checksums.h"
