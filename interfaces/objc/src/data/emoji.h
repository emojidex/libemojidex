
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

// unsigned int times_favorited;
- (void)setTimesFavorited:(unsigned int)timesFavorited;
- (unsigned int)getTimesFavorited;

// int score;
- (void)setScore:(int)score;
- (int)getScore;

// std::string attribution;
- (void)setAttribution:(NSString*)attribution;
- (NSString*)getAttribution;

// std::string user_id;
- (void)setUserId:(NSString*)userId;
- (NSString*)getUserId;

// double current_price;
- (void)setCurrentPrice:(double)currentPrice;
- (double)getCurrentPrice;

// bool primary;
- (void)setPrimary:(BOOL)primary;
- (BOOL)getPrimary;

// bool permalock;
- (void)setPermalock:(BOOL)permalock;
- (BOOL)getPermalock;

// std::string registered_at;
- (void)setRegisteredAt:(NSString*)registeredAt;
- (NSString*)getRegisteredAt;

// std::string link_expiration;
- (void)setLinkExpiration:(NSString*)linkExpiration;
- (NSString*)getLinkExpiration;

// std::string lock_expiration;
- (void)setLockExpiration:(NSString*)lockExpiration;
- (NSString*)getLockExpiration;

// unsigned int times_changed;
- (void)setTimesChanged:(unsigned int)timesChanged;
- (unsigned int)getTimesChanged;

// unsigned int favorited;
- (void)setFavorited:(unsigned int)favorited;
- (unsigned int)getFavorited;

// Emojidex::Data::Checksums checksums;
- (void)setChecksums:(Emojidex_Data_Checksums*)checksums;
- (Emojidex_Data_Checksums*)getChecksums;

// void fillFromJSONString(std::string json);
// void fillFromJSON(rapidjson::Value& d);

@end
