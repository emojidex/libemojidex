#ifndef EMOJIDEX_SERVICE_SETTINGS_H
#define EMOJIDEX_SERVICE_SETTINGS_H

#include <string>
using namespace std;

namespace Emojidex {
	namespace Service {
		class Settings
		{
		public:
			static bool initialized;
			static string api_host;
			static string api_prefix;
			static string api_protocol;
			static string cdn_host;
			static string cdn_prefix;
			static string cdn_protocol;
			static bool	  closed_net;
			static string token;
			
		};
	}
}


#endif // EMOJIDEX_SERVICE_SETTINGS_H
