%module(package="Emojidex") "Emojidex::Client"

%nspace Emojidex::Client;

%{
#include "client.h"
%}

// %include "client.h"
namespace Emojidex {
  //! Core client class (includes all components in a central state-machine client)
  /*!
   * In general you'll want to run everything through a client as long as you are 
   * implementing something with a single user. Multiple client instances could 
   * produce unpredicable behaviour and should be avoided. By loggin in with the 
   * User instance of this client class user details will automatically be set 
   * on appropriate queries.
   */
  class Client
  {
  private:
  public:
    //! Client user instance
    Emojidex::Service::User *User;
    //! Client search instance
    Emojidex::Service::Search *Search;
    //! Client index instance
    Emojidex::Service::Indexes *Indexes;

    Client();
    ~Client();
    char apiVersion();
  }; // Client
} // Emojidex namespace
