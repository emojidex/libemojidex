
#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>

@interface Emojidex_Service_QueryOpts : NSObject
{
@private
  void* _impl;
  BOOL _autoDelete;
}

- (id)init;
- (void)dealloc;

// Sets defaults for a collection
- (void)setCollectionDefaults;

// Chain method to set "locale"
- (Emojidex_Service_QueryOpts*)locale;
- (Emojidex_Service_QueryOpts*)locale:(NSString*)locale;

// Gets current value of "locale" or returns default of "en" if not set
// DOES NOT set value of "locale" if locale is not set
- (NSString*)getLocale;

// Chain method to set "page" by unsigned int
- (Emojidex_Service_QueryOpts*)page;
- (Emojidex_Service_QueryOpts*)page:(unsigned int)number;

// Gets current value of "page" or returns default of 1 if not set
// DOES NOT set value of "page" if page is not set
- (unsigned int)getPage;

// Chain method to set "limit" by unsigned int
- (Emojidex_Service_QueryOpts*)limit;
- (Emojidex_Service_QueryOpts*)limit:(unsigned int)value;

// Gets current value of "limit" or returns default (50) if not set
// DOES NOT set value of "limit" if limit is not set
- (unsigned int)getLimit;

// Chain method to set "detailed" by bool
- (Emojidex_Service_QueryOpts*)detailed;
- (Emojidex_Service_QueryOpts*)detailed:(BOOL)detail;

// Gets current value of "detailed" or returns true if not set
// DOES NOT set value of "detailed" if detailed is not set
- (BOOL)getDetailed;

// Chain method to set "username"
- (Emojidex_Service_QueryOpts*)username;
- (Emojidex_Service_QueryOpts*)username:(NSString*)username;

// Gets current value of "username" or returns empty string if not set
// DOES NOT set value of "username" if username is not set
- (NSString*)getUsername;

// Chain method to set "auth_token"
- (Emojidex_Service_QueryOpts*)authToken;
- (Emojidex_Service_QueryOpts*)authToken:(NSString*)authToken;

// Gets current value of "auth_token" or returns empty string if not set
// DOES NOT set value of "auth_token" if username is not set
- (NSString*)getAuthToken;

// Chain method to add a tag string to the tags vector
- (Emojidex_Service_QueryOpts*)tag:(NSString*)tag;

// Clear current value of "tags"
- (Emojidex_Service_QueryOpts*)clearTags;

// Gets current value of "tags" or returns empty vector if not set
// DOES NOT set value of "tags" if tags is not set
- (NSArray*)getTags;

// Chain method to add a category string to the categories vector
- (Emojidex_Service_QueryOpts*)category:(NSString*)category;

// Clear current value of "categories"
- (Emojidex_Service_QueryOpts*)clearCategories;

// Gets current value of "categories" or returns empty vector if not set
// DOES NOT set value of "categories" if categories is not set
- (NSArray*)getCategories;

// Adds an opt to the ext_opts string with a prefixed "&" (or custom prefix when specified)
- (Emojidex_Service_QueryOpts*)ext:(NSString*)opt;
- (Emojidex_Service_QueryOpts*)ext:(NSString*)opt prefix:(NSString*)prefix;

// Clear ext opts string
- (Emojidex_Service_QueryOpts*)clearExt;

// Get ext opt string
- (NSString*)getExt;

//- (Emojidex_Service_QueryOpts*)parseUnorderedMap:(NSObject*)source_map;
- (NSString*)toString;

@end
