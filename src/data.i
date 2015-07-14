%module(package="Emojidex") "Emojidex::Data"

%{
#include "data.h"
%}

%import "data/emoji.i"
%import "data/collection.i"

namespace Emojidex {
    namespace Data {
    }
}
