%module(package="Emojidex::Data") "Emojidex::Data::Combination"

%nspace Emojidex::Data::Combination;

%include "StringVector.i"
%include "unordered_map_string_checksums.i"

// For java.
SWIG_JAVABODY_PROXY(public, public, SWIGTYPE)
SWIG_JAVABODY_TYPEWRAPPER(public, public, public, SWIGTYPE)
%template(UintVector) std::vector<unsigned int>;
%template(StringVectorVector) std::vector< std::vector<std::string> >;
%template(ChecksumsMapVector) std::vector< std::unordered_map<std::string, Emojidex::Data::Checksums> >;

%typemap(javaimports) Emojidex::Data::Combination %{
import com.emojidex.libemojidex.UintVector;
import com.emojidex.libemojidex.StringVectorVector;
import com.emojidex.libemojidex.ChecksumsMapVector;
%}

%{
#include "data/combination.h"
%}

%include "data/combination.h"
