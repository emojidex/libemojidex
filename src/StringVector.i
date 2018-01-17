
%include <std_string.i>
%include <std_vector.i>

SWIG_JAVABODY_PROXY(public, public, SWIGTYPE)
SWIG_JAVABODY_TYPEWRAPPER(public, public, public, SWIGTYPE)

%template(StringVector) std::vector<std::string>;
