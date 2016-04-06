%module(package="Emojidex::Service") "Emojidex::Service::User"

%nspace Emojidex::Service::User;

%include <std_string.i>
%include <std_vector.i>

// For java.
%typemap(javaimports) Emojidex::Service::User %{
import com.emojidex.libemojidex.HistoryItemVector;
%}

%{
#include "service/user.h"
%}

// %include "service/user.h"
namespace Emojidex {
  namespace Service {
    class User
    {
    private:
      // Merges a page of history items into the history list
      void mergeHistoryPage(std::vector<Emojidex::Service::HistoryItem> history_page);
      // Merges a single history item into the history list.
      // Returns true if the item was already in the history list and was updated.
      // Retruns false if the item was newly added.
      bool mergeHistoryItem(Emojidex::Service::HistoryItem history_item);
      // Sorts history list by last_used
      void sortHistory();

    public:
      enum AuthStatusCode
      {
        NONE,
        FAILURE,
        UNVERIFIED,
        VERIFIED
      };

      AuthStatusCode status;
      std::string username;
      std::string auth_token;
      bool pro;
      std::string pro_exp;
      bool premium;
      std::string premium_exp;
      bool r18;
      // WARNING: debug
      std::string response;

      User();
      ~User();

      bool authorize(std::string username, std::string token);

      bool login(std::string user, std::string password);

      Emojidex::Data::Collection favorites;
      bool syncFavorites(bool detailed = true);
      bool addFavorite(std::string code);
      bool removeFavorite(std::string code);

      std::vector<Emojidex::Service::HistoryItem> history;
      unsigned int history_total;
      unsigned int history_page;
      // Syncs history.
      // Consecutive calls [with page set to 0] will get the next page after history_page.
      std::vector<Emojidex::Service::HistoryItem> syncHistory(unsigned int page = 0, unsigned int limit = DEFAULT_LIMIT);
      bool addHistory(std::string code);
    };
  }
}

// Rename template classes.
#ifndef TEMPLATE_HISTORY_ITEM_VECTOR
#define TEMPLATE_HISTORY_ITEM_VECTOR
%template(HistoryItemVector) std::vector<Emojidex::Service::HistoryItem>;
#endif
