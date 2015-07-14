%module(package="Emojidex") "Emojidex::Data"

%{
#import "data.h"
#define Init_Emojidex Init_Emojidex_Data
%}

%import "data/emoji.i"
%import "data/collection.i"

namespace Emojidex {
    namespace Data {
    }
}
