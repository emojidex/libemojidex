%module(package="Emojidex:::Data") "Emojidex::Data::Collection"

%nspace Emojidex::Data::Collection;

%include <std_string.i>
%include <std_vector.i>
%include "unordered_map_string_emoji.i"

// For java.
SWIG_JAVABODY_PROXY(public, public, SWIGTYPE)
SWIG_JAVABODY_TYPEWRAPPER(public, public, public, SWIGTYPE)
%template(EmojiVector) std::vector<Emojidex::Data::Emoji>;

%typemap(javaimports) Emojidex::Data::Collection %{
import com.emojidex.libemojidex.EmojiVector;
%}

%{
#include "data/collection.h"
%}

// Ignore operator overrides
%ignore Emojidex::Data::Collection::operator<<;

// Ignore function pointers
%ignore Emojidex::Data::Collection::moreMethod;
%ignore Emojidex::Data::Collection::setPagination;

%include "data/collection.h"
