
#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>

#import "../data/moji_codes.h"
#import "../data/collection.h"

@interface Emojidex_Service_Indexes : NSObject
{
@private
  void* _impl;
  BOOL _autoDelete;
}

- (id)init;
- (void)dealloc;

- (Emojidex_Data_MojiCodes*)mojiCodes;
- (Emojidex_Data_MojiCodes*)mojiCodes:(NSString*)locale;

// - (Emojidex_Data_Collection*)utfEmoji;
// - (Emojidex_Data_Collection*)utfEmoji:(NSString*)locale;
// - (Emojidex_Data_Collection*)utfEmoji:(NSString*)locale detailed:(BOOL)detailed;

// - (Emojidex_Data_Collection*)extendEmoji;
// - (Emojidex_Data_Collection*)extendEmoji:(NSString*)locale;
// - (Emojidex_Data_Collection*)extendEmoji:(NSString*)locale detailed:(BOOL)detailed;

// + (Emojidex_Data_Collection*)nextPage:(Emlojidex_Data_Collection*)collection;

// - (Emojidex_Data_Collection*)emoji;
// - (Emojidex_Data_Collection*)emoji:(unsigned int)limit;
// - (Emojidex_Data_Collection*)emoji:(unsigned int)limit page:(unsigned int)page;
// - (Emojidex_Data_Collection*)emoji:(unsigned int)limit page:(unsigned int)page detailed:(BOOL)detailed;

// - (Emojidex_Data_Collection*)newest;
// - (Emojidex_Data_Collection*)newest:(unsigned int)limit;
// - (Emojidex_Data_Collection*)newest:(unsigned int)limit page:(unsigned int)page;
// - (Emojidex_Data_Collection*)newest:(unsigned int)limit page:(unsigned int)page detailed:(BOOL)detailed;

// - (Emojidex_Data_Collection*)popular;
// - (Emojidex_Data_Collection*)popular:(unsigned int)limit;
// - (Emojidex_Data_Collection*)popular:(unsigned int)limit page:(unsigned int)page;
// - (Emojidex_Data_Collection*)popular:(unsigned int)limit page:(unsigned int)page detailed:(BOOL)detailed;

@end
