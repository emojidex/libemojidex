%module(package="Emjidex::Data") "Emojidex::Data::MojiCodes"

%nspace Emojidex::Data::MojiCodes;

%include "string_vector.i"
%include "unordered_map_string_string.i"

// For java.
%typemap(javaimports) Emojidex::Data::MojiCodes %{
import com.emojidex.libemojidex.StringVector;
%}

%{
#include "data/moji_codes.h"
%}

%include "data/moji_codes.h"

