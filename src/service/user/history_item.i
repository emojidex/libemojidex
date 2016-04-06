%module(package="Emojidex::Service") "Emojidex::Service::HistoryItem"

%nspace Emojidex::Service::HistoryItem;

%include <std_string.i>

%{
#include "service/user/history_item.h"
%}

// Ignore boost.
%ignore Emojidex::Service::HistoryItem::last_used_posix;

// %include "service/user/history_item.h"
namespace Emojidex {
  namespace Service {
    class HistoryItem {
      public:

      std::string emoji_code;
      unsigned int times_used;
      std::string last_used;
      boost::posix_time::ptime last_used_posix;

      HistoryItem();
      HistoryItem(std::string emoji_code, unsigned int times_used, std::string last_used);
    };
  }
}
