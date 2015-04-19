#include "settings.h"

std::string Emojidex::Service::Settings::api_host		= "www.emojidex.com";
std::string Emojidex::Service::Settings::api_prefix		= "/api/v1/";
std::string Emojidex::Service::Settings::api_protocol	= "https";
std::string Emojidex::Service::Settings::cdn_host		= "cdn.emojidex.com";
std::string Emojidex::Service::Settings::cdn_prefix		= "/emoji/";
std::string Emojidex::Service::Settings::cdn_protocol	= "http";
bool		Emojidex::Service::Settings::closed_net		= false;
std::string Emojidex::Service::Settings::token			= "";
bool		Emojidex::Service::Settings::initialized	= true;
