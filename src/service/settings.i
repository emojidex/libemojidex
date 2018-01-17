%module(package="Emojidex::Service") "Emojidex::Service::Settings"

%nspace Emojidex::Service::Settings;

%include <std_string.i>

%{
#include "service/settings.h"
%}

%include "service/settings.h"
