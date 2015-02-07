/******************************************************************************
 * emojidex client
 * Authors: Rei Kagetsuki
 * Copyright: Genshin Souzou Kabushiki Kaisha and Rei Kagetsuki 2015~
 * License: emojidex Open License
 *
 * This module provides full client access through the emojidex API
 * General usage documentation: http://developer.emojidex.com
 * *detailed documentation can be generated by doxygen and is bundled 
 * *with the c-emojidex repository.
 *****************************************************************************/
#ifndef EMOJIDEX_CLIENT_H
#define EMOJIDEX_CLIENT_H

#include "client/transactor.h"
#include "client/search.h"

#include <string>
using namespace std;

namespace Emojidex {
	// Core client class (includes all components in a central state-machine client)
	class Client
	{
	private:
		//Emojidex::Transactor *transactor;
	public:
		Emojidex::SearchClient *Search;

		Client();
		char apiVersion();
	}; // Client
} // Emojidex namespace

#endif // EMOJIDEX_CLIENT_H
