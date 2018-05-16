
%include <std_string.i>
%include <std_vector.i>
%include "cstring_to_jstring.i"

%typemap(out) const std::string&
{
  $result = cstr2jstr(jenv, *$1);
}

SWIG_JAVABODY_PROXY(public, public, SWIGTYPE)
SWIG_JAVABODY_TYPEWRAPPER(public, public, public, SWIGTYPE)

%template(StringVector) std::vector<std::string>;
