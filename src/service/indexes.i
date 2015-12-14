%module(package="Emojidex::Service") "Emojidex::Service::Indexes"

%nspace Emojidex::Service::Indexes;

%include <std_string.i>

%{
#include "service/indexes.h"
%}

namespace Emojidex {
  namespace Service {
    // Retrieves data from emojidex indexes
    class Indexes
    {
    private:
      Emojidex::Data::MojiCodes *codes;
    public:
      Indexes();
      ~Indexes();


      /* NOTE: all calls default to locale = "en" and detailed = false */

      //=====================================================================================
      // Static Seeds
      // ============

      // Get standard UTF emoji info in 3 compact forms
      Emojidex::Data::MojiCodes mojiCodes(std::string locale = "");
      // Get a collection of all standard UTF emoji
      Emojidex::Data::Collection utfEmoji(std::string locale = "", bool detailed = false);
      // Get a collection of all emojidex Extended emoji
      Emojidex::Data::Collection extendedEmoji(std::string locale = "", bool detailed = false);
      
      //=====================================================================================
      // Dynamic Indexes
      // ===============

      // Get full emoji index by score
      Emojidex::Data::Collection emoji(unsigned int page = Emojidex::Service::Collector::DefaultPage, 
          unsigned int limit = DEFAULT_LIMIT, bool detailed = false);
      // Get Newest emoji
      Emojidex::Data::Collection newest(unsigned int page = Emojidex::Service::Collector::DefaultPage,
          unsigned int limit = DEFAULT_LIMIT, bool detailed = false);

      // Get most Popular emoji
      Emojidex::Data::Collection popular(unsigned int page = Emojidex::Service::Collector::DefaultPage,
          unsigned int limit = DEFAULT_LIMIT, bool detailed = false);
    };
  }
}
