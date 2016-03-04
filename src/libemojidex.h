#ifndef _LIBEMOJIDEX_H_
#define _LIBEMOJIDEX_H_

#include "./data.h"
#include <string>
//#include "./data/collection.h"

//#include "./client.h"
//#include "./service/indexes.h"
//#include "./service/search.h"

namespace Emojidex {
	const char encapsulator = ':';
	std::string escapeCode(std::string code);
	std::string unescapeCode(std::string code);
	std::string encapsulateCode(std::string code);
	std::string unencapsulateCode(std::string code);

  void setCACertPath(const std::string &path = "");
  const std::string& getCACertPath(void);
}

#endif /* _LIBEMOJIDEX_H_ */
