%module(package="Emojidex::Service") "Emojidex::Service::QueryOpts"

%nspace Emojidex::Service::QueryOpts;

%include "string_vector.i"
%include "unordered_map_string_string.i"

// For java.
%typemap(javaimports) Emojidex::Service::QueryOpts %{
import com.emojidex.libemojidex.StringVector;
%}

%{
#include "service/query_opts.h"
%}

%include "service/query_opts.h"
