%module(package="Emojidex::Service") "Emojidex::Service::Indexes"

%nspace Emojidex::Service::Indexes;

%include <std_string.i>

%{
#include "service/indexes.h"
%}

%include "service/indexes.h"
