%module(package="Emojidex::Service") "Emojidex::Service::HistoryItem"

%nspace Emojidex::Service::HistoryItem;

%include <std_string.i>

%{
#include "service/user/history_item.h"
%}

// Ignore boost.
%ignore Emojidex::Service::HistoryItem::last_used_posix;

%include "service/user/history_item.h"
