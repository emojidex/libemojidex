#include "client.h"

Emojidex::Client::Client()
{
  this->User = new Emojidex::Service::User();
	this->Search = new Emojidex::Service::Search();
  this->Indexes = new Emojidex::Service::Indexes();
}

Emojidex::Client::~Client()
{
  if(this->User != NULL)
  {
    delete this->User;
    this->User = NULL;
  }
  if(this->Search != NULL)
  {
    delete this->Search;
    this->Search = NULL;
  }
  if(this->Indexes != NULL)
  {
    delete this->Indexes;
    this->Indexes = NULL;
  }
}

char Emojidex::Client::apiVersion()
{
	return 1;
}
