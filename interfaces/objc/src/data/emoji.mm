
#import "emoji.h"
#import "emoji+private.h"

#import "checksums+private.h"
#import "../utils+private.h"

typedef Emojidex::Data::Emoji ImplType;
#define IMPL ((ImplType*)_impl)

@implementation Emojidex_Data_Emoji (Private)

- (id)initWithEmoji:(const Emojidex::Data::Emoji&)src
{
  self = [super init];
  if(self != nil)
  {
    _impl = new ImplType();
    *IMPL = src;
    _autoDelete = YES;
  }
  else
    _autoDelete = NO;
  return self;
}

- (const Emojidex::Data::Emoji*)getImpl
{
  return IMPL;
}

@end

@implementation Emojidex_Data_Emoji

- (id)init
{
  self = [super init];
  if(self != nil)
  {
    _impl = new ImplType();
    _autoDelete = YES;
  }
  else
    _autoDelete = NO;
  return self;
}

- (void)dealloc
{
  if(_autoDelete)
  {
    delete IMPL;
    _impl = nil;
  }
  [super dealloc];
}

- (void)setMoji:(NSString*)moji
{
  IMPL->moji = NS2STD(moji);
}

- (NSString*)getMoji
{
  return STD2NS(IMPL->moji);
}

- (void)setCode:(NSString*)code
{
  IMPL->code = NS2STD(code);
}

- (NSString*)getCode
{
  return STD2NS(IMPL->code);
}

- (void)setUnicode:(NSString*)unicode
{
  IMPL->unicode = NS2STD(unicode);
}

- (NSString*)getUnicode
{
  return STD2NS(IMPL->unicode);
}

- (void)setCategory:(NSString*)category
{
  IMPL->category = NS2STD(category);
}

- (NSString*)getCategory
{
  return STD2NS(IMPL->category);
}

// // std::vector<std::string> tags;
- (void)setTags:(NSArray*)tags
{
  IMPL->tags.clear();
  const int size = [tags count];
  for(int i = 0;  i < size;  ++i)
    IMPL->tags.push_back(NS2STD([tags objectAtIndex:i]));
}

- (NSArray*)getTags
{
  NSMutableArray* newArray = [NSMutableArray array];
  const size_t size = IMPL->tags.size();
  for(size_t i = 0;  i < size;  ++i)
    [newArray addObject:STD2NS(IMPL->tags[i])];
  return [newArray copy];
}

- (void)setBase:(NSString*)base
{
  IMPL->base = NS2STD(base);
}

- (NSString*)getBase
{
  return STD2NS(IMPL->base);
}

- (void)setVariants:(NSArray*)variants
{
  IMPL->variants.clear();
  const int size = [variants count];
  for(int i = 0;  i < size;  ++i)
    IMPL->variants.push_back(NS2STD([variants objectAtIndex:i]));
}

- (NSArray*)getVariants
{
  NSMutableArray* newArray = [NSMutableArray array];
  const size_t size = IMPL->variants.size();
  for(size_t i = 0;  i < size;  ++i)
    [newArray addObject:STD2NS(IMPL->variants[i])];
  return [newArray copy];
}

- (void)setLink:(NSString*)link
{
  IMPL->link = NS2STD(link);
}

- (NSString*)getLink
{
  return STD2NS(IMPL->link);
}

- (void)setIsWide:(BOOL)isWide
{
  IMPL->is_wide = isWide;
}

- (BOOL)getIsWide
{
  return IMPL->is_wide;
}

- (void)setCopyrightLock:(BOOL)copyrightLock
{
  IMPL->copyright_lock = copyrightLock;
}

- (BOOL)getCopyrightLock
{
  return IMPL->copyright_lock;
}

- (void)setTimesUsed:(int)timesUsed
{
  IMPL->times_used = timesUsed;
}

- (int)getTimesUsed
{
  return IMPL->times_used;
}

- (void)setTimesFavorited:(unsigned int)timesFavorited
{
  IMPL->times_favorited = timesFavorited;
}

- (unsigned int)getTimesFavorited
{
  return IMPL->times_favorited;
}

- (void)setScore:(int)score
{
  IMPL->score = score;
}

- (int)getScore
{
  return IMPL->score;
}

- (void)setAttribution:(NSString*)attribution
{
  IMPL->attribution = NS2STD(attribution);
}

- (NSString*)getAttribution
{
  return STD2NS(IMPL->attribution);
}

- (void)setUserId:(NSString*)userId
{
  IMPL->user_id = NS2STD(userId);
}

- (NSString*)getUserId
{
  return STD2NS(IMPL->user_id);
}

- (void)setCurrentPrice:(double)currentPrice
{
  IMPL->current_price = currentPrice;

}
- (double)getCurrentPrice
{
  return IMPL->current_price;
}

- (void)setPrimary:(BOOL)primary
{
  IMPL->primary = primary;
}

- (BOOL)getPrimary
{
  return IMPL->primary;
}

- (void)setPermalock:(BOOL)permalock
{
  IMPL->permalock = permalock;
}

- (BOOL)getPermalock
{
  return IMPL->permalock;
}

- (void)setRegisteredAt:(NSString*)registeredAt
{
  IMPL->registered_at = NS2STD(registeredAt);
}

- (NSString*)getRegisteredAt
{
  return STD2NS(IMPL->registered_at);
}

- (void)setLinkExpiration:(NSString*)linkExpiration
{
  IMPL->link_expiration = NS2STD(linkExpiration);
}

- (NSString*)getLinkExpiration
{
  return STD2NS(IMPL->link_expiration);
}

- (void)setLockExpiration:(NSString*)lockExpiration
{
  IMPL->lock_expiration = NS2STD(lockExpiration);
}

- (NSString*)getLockExpiration
{
  return STD2NS(IMPL->lock_expiration);
}

- (void)setTimesChanged:(unsigned int)timesChanged
{
  IMPL->times_changed = timesChanged;
}

- (unsigned int)getTimesChanged
{
  return IMPL->times_changed;
}

- (void)setFavorited:(unsigned int)favorited
{
  IMPL->favorited = favorited;
}

- (unsigned int)getFavorited
{
  return IMPL->favorited;
}

- (void)setChecksums:(Emojidex_Data_Checksums*)checksums
{
  IMPL->checksums = *[checksums getImpl];
}

- (Emojidex_Data_Checksums*)getChecksums
{
  return [[[Emojidex_Data_Checksums alloc] initWithChecksums:IMPL->checksums] autorelease];
}

@end
