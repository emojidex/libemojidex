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
    //! Container for entries in a users history
    class HistoryItem {
      public:

      //! The code of the emoji used
      std::string emoji_code;
      //! The number of times the user has used this emoji
      unsigned int times_used;
      //! String noting the last time the emoji was used 
      std::string last_used;
      //! POSIX time object with the last time the emoji was used
      boost::posix_time::ptime last_used_posix;

      HistoryItem();
      //! Quickly initialize a filled HistoryItem object
      HistoryItem(std::string emoji_code, unsigned int times_used, std::string last_used);
    };
  }
}
