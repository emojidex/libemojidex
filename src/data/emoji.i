%module(package="Emojidex::Data") "Emojidex::Data::Emoji"

%nspace Emojidex::Data::Emoji;

%include "string_vector.i"
%include "cstring_to_jstring.i"

// For java.
SWIG_JAVABODY_PROXY(public, public, SWIGTYPE)
SWIG_JAVABODY_TYPEWRAPPER(public, public, public, SWIGTYPE)
%template(CombinationVector) std::vector<Emojidex::Data::Combination>;

%typemap(javaimports) Emojidex::Data::Emoji %{
import com.emojidex.libemojidex.StringVector;
import com.emojidex.libemojidex.CombinationVector;
%}

#ifdef SWIGJAVA
%typemap(out) const std::string&
{
  $result = cstr2jstr(jenv, *$1);
}
#endif

%{
#include "data/emoji.h"
%}

// Ignore rapidjson.
%ignore Emojidex::Data::Emoji::fillFromJSON;
%ignore Emojidex::Data::Emoji::fillFromMsgPack;

%include "data/emoji.h"
