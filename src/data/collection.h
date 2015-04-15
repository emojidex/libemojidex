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
      bool detailed;
      string locale;
      unordered_map<string, Emojidex::Data::Emoji> emoji;

      // Get more of the collection if the collection is paginated and has remaining pages.
      // Returns true if the next page was sucessfully obtained. Returns false if there are no 
      // more pages/emoji to obtain.
      Emojidex::Data::Collection more();

      // Called when more() is invoked.
      // Results are combined into this collection but a collection with just the new results is 
      // returned.
      Emojidex::Data::Collection *moreMethod;
      unsigned int page;
      unsigned short limit;
      unsigned int total_count;
      // Sets up collection as a paged collection (with more pages/emoji remaining on the service).
      void setPagination(Emojidex::Data::Collection (*moreMethod)(Emojidex::Data::Collection, unsigned int), unsigned int starting_page, unsigned int limit);
    };
  }
}

#endif /* EMOJIDEX_DATA_COLLECTION_H */
