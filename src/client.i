%module Client

// Include STL header files.
%include "std_string.i"
%include "std_vector.i"

// 
%{
#include "client.h"
#include "service/settings.h"
#include "service/transactor.h"
%}

// Include header files.
// Prototype.
namespace Emojidex {
  namespace Service {
    class Indexes;
    class Search;
    class Settings;
    class Transactor;
  }
  namespace Data {
    class Collection;
    class MojiCodes;
    class Emoji;
    class Checksums;
  }
  class Client;
}

// %include "client.h"
namespace Emojidex {
  // Core client class (includes all components in a central state-machine client)
  class Client
  {
  private:
    //Emojidex::Transactor *transactor;
  public:
    Emojidex::Service::Search *Search;
    Emojidex::Service::Search *Indexes;

    Client();
    char apiVersion();
  }; // Client
} // Emojidex namespace

// %include "service/search.h"
namespace Emojidex {
  namespace Service {
    class Search
    {
    public:
      unsigned int current_page;

      Search();
      Emojidex::Data::Collection term(std::string term);
    };
  }
}

// %include "service/settings.h"
namespace Emojidex {
  namespace Service {
    class Settings
    {
    public:
      static bool        initialized;
      static std::string api_host;
      static std::string api_prefix;
      static std::string api_protocol;
      static std::string cdn_host;
      static std::string cdn_prefix;
      static std::string cdn_protocol;
      static bool        closed_net;
      static std::string token;
    };
  }
}
