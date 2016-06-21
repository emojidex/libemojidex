%module(package="Emojidex::Service") "Emojidex::Service::Settings"

%nspace Emojidex::Service::Settings;

%include <std_string.i>

%{
#include "service/settings.h"
%}

namespace Emojidex {
  namespace Service {
    //! Service client settings. Generally should not be touched.
    class Settings
    {
    public:
      //! Flag indicating if service constants have been initialized
      /*!
       * This is currently short-circuited to "true".
       */
      static bool        initialized;
      //! API host domain
      static std::string api_host;
      //! API endpoint prefix
      static std::string api_prefix;
      //! API access protocol
      static std::string api_protocol;
      //! CDN host domain
      static std::string cdn_host;
      //! CDN endpoint prefix
      static std::string cdn_prefix;
      //! CDN access protocol
      static std::string cdn_protocol;
      //! Special flag to specify that endpoints are on a closed network, not the official service
      /*!
       * As using closed_net functionality generally violates the emojidex Open License for 
       * many use cases this feature isn't actually implemented. In the future if will be implemented 
       * if there is enough demand from closed-source and commercial license holders.
       */
      static bool        closed_net;
      //! Sets a global access token (not automatically used)
      static std::string token;
    };
  }
}
