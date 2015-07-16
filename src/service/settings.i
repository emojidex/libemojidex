%module(package="Emojidex::Service") "Emojidex::Service::Settings"

%nspace Emojidex::Service::Settings;

%include <std_string.i>

%{
#include "service/settings.h"
%}

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
