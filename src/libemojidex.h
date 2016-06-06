#ifndef _LIBEMOJIDEX_H_
#define _LIBEMOJIDEX_H_

/*! \mainpage libemojidex Portable Low-Level Client Package
 *
 * \section intro_sec Introduction
 *
 * libemojidex provides a full set of tools to access and operate the 
 * emojidex API. It's written in C++ and has a variety of interfaces and 
 * packaging methods available. Please see the README.md file for more 
 * information including build instructions. libemojidex is hosted on 
 * github at https://github.com/emojidex/libemojidex .
 *
 * \subsection License
 *
 * emojidex and emojidex tools are licensed under the emojidex Open License
 * https://www.emojidex.com/emojidex/emojidex_open_license
 *  
 *****************************************************************************/

#include "./data.h"
#include <string>

namespace Emojidex {
	//! Encapsulation character which surrounds short codes
	const char encapsulator = ':';
	//! Escape a code for transmision
	std::string escapeCode(std::string code);
	//! Unescape a code for display
	std::string unescapeCode(std::string code);
	//! Surround a code in encapsulators
	std::string encapsulateCode(std::string code);
	//! Remove encapsulators around a code
	std::string unencapsulateCode(std::string code);

	//! Set the path to the CA certificate for SSL
	void setCACertPath(const std::string &path = "");
	//! Get the [current/system] path to the CA certificate
	const std::string& getCACertPath(void);
}

#endif /* _LIBEMOJIDEX_H_ */
