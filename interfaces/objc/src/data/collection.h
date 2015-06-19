
#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>

#import "emoji.h"

// emoji base data
@interface Emojidex_Data_Collection : NSObject
{
@private
  void* _impl;
  BOOL _autoDelete;
}

- (id)init;
- (void)dealloc;

// - (void)setEmoji:(Emojidex::Data::UnorderedMap<std::string, Emojidex::Data::Emoji>)mojiIndex;
// - (Emojidex::Data::UnorderedMap<std::string, Emojidex::Data::Emoji>)getEmoji;

//=====================================================================================
// Broken out operations on the emoji map (for interfaces or implementations 
// without map functionality)
// ============
// Returns a vector array of all emoji in the collection
- (NSArray*)all;

// Adds an emoji to the map
- (Emojidex_Data_Emoji*)add:(Emojidex_Data_Emoji*)newEmoji;

// Finds by moji[character]code (UTF emoji only)
- (Emojidex_Data_Emoji*)findByMoji:(NSString*)moji;

// Finds by emoji [short] code
- (Emojidex_Data_Emoji*)findByCode:(NSString*)code;

// Finds by Unicode value
// *Unicode value must be lower case
- (Emojidex_Data_Emoji*)findByUnicode:(NSString*)unicode;

//Emojidex::Data::Collection search()
- (Emojidex_Data_Collection*)category:(NSString*)category;

// Merge a collection with this collection, overwriting emoji with the same
// code in this collection. Rerturns this collection after the merge for chaining.
- (Emojidex_Data_Collection*)merge:(Emojidex_Data_Collection*)deltaCollection;

//=====================================================================================
// Service Info
// ============
// std::string endpoint;
- (void)setEndpoint:(NSString*)endpoint;
- (NSString*)getEndpoint;

// bool detailed;
- (void)setDetailed:(BOOL)detailed;
- (BOOL)getDetailed;

// std::string locale;
- (void)setLocale:(NSString*)locale;
- (NSString*)getLocale;

// unsigned int page;
- (void)setPage:(unsigned int)page;
- (unsigned int)getPage;

// unsigned short limit;
- (void)setLimit:(unsigned short)limit;
- (unsigned short)getLimit;

// unsigned int total_count;
- (void)setTotalCount:(unsigned int)totalCount;
- (unsigned int)getTotalCount;

// Get more of the collection if the collection is paginated and has remaining pages.
// Returns true if the next page was sucessfully obtained. Returns false if there are 
// no more pages/emoji to obtain.
- (Emojidex_Data_Collection*)more;

// Sets up collection as a paged collection (with more pages/emoji remaining on the 
// service).
// - (void)setPagination:(Method)method startingPage:(int)startingPage limit:(unsigned int)limit;
// void setPagination(
//   Emojidex::Data::Collection (*moreMethod)(Emojidex::Data::Collection), 
//   unsigned int starting_page, unsigned int limit);

@end
