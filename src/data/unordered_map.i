%module UnorderedMap


%ignore std::unorderd_map;
%ignore initialzer_list;

%{
#include "data/unordered_map.h"
%}

%include "./unordered_map.h"
