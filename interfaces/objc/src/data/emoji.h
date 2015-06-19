
#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>

#import "checksums.h"

// emoji base data
@interface Emojidex_Data_Emoji : NSObject
{
@private
  void* _impl;
  BOOL _autoDelete;
}

- (id)init;
- (void)dealloc;

// std::string moji;
- (void)setMoji:(NSString*)moji;
- (NSString*)getMoji;

// std::string code;
- (void)setCode:(NSString*)code;
- (NSString*)getCode;

// std::string unicode;
- (void)setUnicode:(NSString*)unicode;
- (NSString*)getUnicode;

// std::string category;
- (void)setCategory:(NSString*)category;
- (NSString*)getCategory;

// std::vector<std::string> tags;
- (void)setTags:(NSArray*)tags;
- (NSArray*)getTags;

// std::string base;
- (void)setBase:(NSString*)base;
- (NSString*)getBase;

// std::vector<std::string> variants;
- (void)setVariants:(NSArray*)variants;
- (NSArray*)getVariants;

// std::string link;
- (void)setLink:(NSString*)link;
- (NSString*)getLink;

// detailed
// bool is_wide;
- (void)setIsWide:(BOOL)isWide;
- (BOOL)getIsWide;

// bool copyright_lock;
- (void)setCopyrightLock:(BOOL)copyrightLock;
- (BOOL)getCopyrightLock;

// int times_used;
- (void)setTimesUsed:(int)timesUsed;
- (int)getTimesUsed;

// std::string attribution;
- (void)setAttribution:(NSString*)attribution;
- (NSString*)getAttribution;

// std::string user_id;
- (void)setUserId:(NSString*)userId;
- (NSString*)getUserId;

// Emojidex::Data::Checksums checksums;
- (void)setChecksums:(Emojidex_Data_Checksums*)checksums;
- (Emojidex_Data_Checksums*)getChecksums;

@end
