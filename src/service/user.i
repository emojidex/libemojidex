%module(package="Emojidex::Service") "Emojidex::Service::User"

%nspace Emojidex::Service::User;

%include "string_vector.i"

// For java.
SWIG_JAVABODY_PROXY(public, public, SWIGTYPE)
SWIG_JAVABODY_TYPEWRAPPER(public, public, public, SWIGTYPE)
%template(HistoryItemVector) std::vector<Emojidex::Service::HistoryItem>;

%typemap(javaimports) Emojidex::Service::User %{
import com.emojidex.libemojidex.HistoryItemVector;
import com.emojidex.libemojidex.StringVector;
%}

%{
#include "service/user.h"
%}

%include "service/user.h"
