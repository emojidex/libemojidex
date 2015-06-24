%module UnorderedMap


%ignore Emojidex::Data::UnorderedMap::base;

%{
#include "data/unordered_map.h"
%}

%include "./unordered_map.h"
