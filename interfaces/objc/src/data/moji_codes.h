
#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>

// Moji code container with 3 types of moji code indexes
@interface Emojidex_Data_MojiCodes : NSObject
{
@private
  void* _impl;
  BOOL _autoDelete;
}

- (id)init;
- (void)dealloc;

// std::string locale;
- (void)setLocale:(NSString*)locale;
- (NSString*)getLocale;

// std::string moji_string;
- (void)setMojiString:(NSString*)mojiString;
- (NSString*)getMojiString;

// std::vector<std::string> moji_array;
- (void)setMojiArray:(NSArray*)mojiArray;
- (NSArray*)getMojiArray;

// Emojidex::Data::UnorderedMap<std::string, std::string> moji_index;
// - (void)setMojiIndex:(NSObject*)mojiIndex;
// - (NSObject*)getMojiIndex;

@end
