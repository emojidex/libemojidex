#ifndef EMOJIDEX_DATA_COLLECTION_H
#define EMOJIDEX_DATA_COLLECTION_H

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#include "./emoji.h"

namespace Emojidex {
	namespace Data {
		// emoji base data
		class Collection
    {
    public:
      string locale;
      unordered_map<string, Emojidex::Data::Emoji> emoji;
    };
  }
}

#endif /* EMOJIDEX_DATA_COLLECTION_H */
