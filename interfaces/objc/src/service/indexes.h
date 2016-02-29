
#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>

#import "../data/moji_codes.h"
#import "../data/collection.h"

// Retrieves data from emojidex indexes
@interface Emojidex_Service_Indexes : NSObject
{
@private
  void* _impl;
  BOOL _autoDelete;
}

- (id)init;
- (void)dealloc;

/* NOTE: all calls default to locale = @"en" and detailed = NO */

//=====================================================================================
// Static Seeds
// ============
// Get standard UTF emoji info in 3 compact forms
- (Emojidex_Data_MojiCodes*)mojiCodes;
- (Emojidex_Data_MojiCodes*)mojiCodes:(NSString*)locale;

// Get a collection of all standard UTF emoji
- (Emojidex_Data_Collection*)utfEmoji;
- (Emojidex_Data_Collection*)utfEmoji:(NSString*)locale;
- (Emojidex_Data_Collection*)utfEmoji:(NSString*)locale detailed:(BOOL)detailed;

// Get a collection of all emojidex Extended emoji
- (Emojidex_Data_Collection*)extendedEmoji;
- (Emojidex_Data_Collection*)extendedEmoji:(NSString*)locale;
- (Emojidex_Data_Collection*)extendedEmoji:(NSString*)locale detailed:(BOOL)detailed;

//=====================================================================================
// Dynamic Indexes
// ===============
+ (Emojidex_Data_Collection*)nextPage:(Emojidex_Data_Collection*)collection;

// Get full emoji index by score
- (Emojidex_Data_Collection*)emoji;
- (Emojidex_Data_Collection*)emoji:(unsigned int)page;
- (Emojidex_Data_Collection*)emoji:(unsigned int)page limit:(unsigned int)limit;
- (Emojidex_Data_Collection*)emoji:(unsigned int)page limit:(unsigned int)limit detailed:(BOOL)detailed;

// Get Newest emoji
- (Emojidex_Data_Collection*)newest:(NSString*)authToken;
- (Emojidex_Data_Collection*)newest:(NSString*)authToken page:(unsigned int)page;
- (Emojidex_Data_Collection*)newest:(NSString*)authToken page:(unsigned int)page limit:(unsigned int)limit;
- (Emojidex_Data_Collection*)newest:(NSString*)authToken page:(unsigned int)page limit:(unsigned int)limit detailed:(BOOL)detailed;

// Get most Popular emoji
- (Emojidex_Data_Collection*)popular:(NSString*)authToken;
- (Emojidex_Data_Collection*)popular:(NSString*)authToken page:(unsigned int)page;
- (Emojidex_Data_Collection*)popular:(NSString*)authToken page:(unsigned int)page limit:(unsigned int)limit;
- (Emojidex_Data_Collection*)popular:(NSString*)authToken page:(unsigned int)page limit:(unsigned int)limit detailed:(BOOL)detailed;

@end
