%module Emojidex_Data_Checksums

%include "std_string.i"
%include "./unordered_map.i"

%{
#include "data/checksums.h"
%}

%include "./checksums.h"