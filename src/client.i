%module(package="Emojidex") "Emojidex::Client"

%nspace Emojidex::Client;

%{
#include "client.h"
%}

// %include "client.h"
namespace Emojidex {
  // Core client class (includes all components in a central state-machine client)
  class Client
  {
  private:
  public:
    Emojidex::Service::User *User;
    Emojidex::Service::Search *Search;
    Emojidex::Service::Indexes *Indexes;

    Client();
    ~Client();
    char apiVersion();
  }; // Client
} // Emojidex namespace
