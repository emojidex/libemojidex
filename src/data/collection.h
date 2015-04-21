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
		private:
			// Called when more() is invoked.
			// Results are combined into this collection but a collection with just the new results 
			// is returned.
			Emojidex::Data::Collection (*moreMethod)(Emojidex::Data::Collection);
		public:
			Collection();
			~Collection();

			unordered_map<string, Emojidex::Data::Emoji> emoji;

			//=====================================================================================
			// Broken out operations on the emoji map (for interfaces or implementations 
			// without map functionality)
			// ============

			// Returns a vector array of all emoji in the collection
			vector<Emojidex::Data::Emoji> all();

			// Adds an emoji to the map
			Emojidex::Data::Emoji add(Emojidex::Data::Emoji new_emoji);

			// Finds by moji[character]code (UTF emoji only)
			Emojidex::Data::Emoji findByMoji(string moji);
			// Finds by emoji [short] code
			Emojidex::Data::Emoji findByCode(string code);
			// Finds by Unicode value
			// *Unicode value must be lower case
			Emojidex::Data::Emoji findByUnicode(string unicode);

			//Emojidex::Data::Collection search()
			Emojidex::Data::Collection category(string category);

			// Merge a collection with this collection, overwriting emoji with the same
			// code in this collection. Rerturns this collection after the merge for chaining.
			Emojidex::Data::Collection merge(Emojidex::Data::Collection delta_collection);
			Emojidex::Data::Collection operator<<(Emojidex::Data::Collection delta_collection);
      
			//=====================================================================================
			// Service Info
			// ============
			string endpoint;
			bool detailed;
			string locale;
			unsigned int page;
			unsigned short limit;
			unsigned int total_count;

			// Get more of the collection if the collection is paginated and has remaining pages.
			// Returns true if the next page was sucessfully obtained. Returns false if there are 
			// no more pages/emoji to obtain.
			Emojidex::Data::Collection more();

			// Sets up collection as a paged collection (with more pages/emoji remaining on the 
			// service).
			void setPagination(
					Emojidex::Data::Collection (*moreMethod)(Emojidex::Data::Collection), 
					unsigned int starting_page, unsigned int limit);
		};
	}
}

#endif /* EMOJIDEX_DATA_COLLECTION_H */
