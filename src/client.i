%module(package="Emojidex") "Emojidex::Client"

%nspace Emojidex::Client;

%{
#include "client.h"
%}

%include "client.h"
