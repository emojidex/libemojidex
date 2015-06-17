
#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>

@interface Emojidex_Data_MojiCodes : NSObject
{
@private
  void* _impl;
  BOOL _autoDelete;
}

- (id)init;
- (void)dealloc;

- (void)setLocale:(NSString*)locale;
- (NSString*)getLocale;

- (void)setMojiString:(NSString*)mojiString;
- (NSString*)getMojiString;

- (void)setMojiArray:(NSArray*)mojiArray;
- (NSArray*)getMojiArray;

// - (void)setMojiIndex:(UnorderedMap<string>)mojiIndex;
// - (UnorderedMap<string>)getMojiIndex;

@end
