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
    //Emojidex::Transactor *transactor;
  public:
    Emojidex::Service::Search *Search;
    Emojidex::Service::Search *Indexes;

    Client();
    char apiVersion();
  }; // Client
} // Emojidex namespace
