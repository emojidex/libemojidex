%module(package="Emojidex::Service") "Emojidex::Service::Search"

%nspace Emojidex::Service::Search;

%include "string_vector.i"

// For java.
%typemap(javaimports) Emojidex::Service::Search %{
import com.emojidex.libemojidex.StringVector;
%}

%{
#include "service/search.h"
%}

%include "service/search.h"
