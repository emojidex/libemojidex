
#import "indexes.h"
#import "indexes+private.h"

#import "../data/moji_codes+private.h"
#import "../data/collection+private.h"
#import "../utils+private.h"

#import "../../../src/service/indexes.h"

typedef Emojidex::Service::Indexes ImplType;
#define IMPL ((ImplType*)_impl)

@implementation Emojidex_Service_Indexes (Private)

- (id)initWithIndexes:(Emojidex::Service::Indexes*)src
{
  self = [super init];
  if(self != nil)
  {
    _impl = src;
  }
  _autoDelete = NO;
  return self;
}

- (Emojidex::Service::Indexes*)getImpl
{
  return IMPL;
}

@end

@implementation Emojidex_Service_Indexes

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

- (Emojidex_Data_MojiCodes*)mojiCodes
{
  const Emojidex::Data::MojiCodes& tmp = IMPL->mojiCodes();
  return [[[Emojidex_Data_MojiCodes alloc] initWithMojiCodes:tmp] autorelease];
}

- (Emojidex_Data_MojiCodes*)mojiCodes:(NSString*)locale
{
  const Emojidex::Data::MojiCodes& tmp = IMPL->mojiCodes(NS2STD(locale));
  return [[[Emojidex_Data_MojiCodes alloc] initWithMojiCodes:tmp] autorelease];
}

- (Emojidex_Data_Collection*)utfEmoji
{
  const Emojidex::Data::Collection& tmp = IMPL->utfEmoji();
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

- (Emojidex_Data_Collection*)utfEmoji:(NSString*)locale
{
  const Emojidex::Data::Collection& tmp = IMPL->utfEmoji(NS2STD(locale));
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

- (Emojidex_Data_Collection*)utfEmoji:(NSString*)locale detailed:(BOOL)detailed
{
  const Emojidex::Data::Collection& tmp = IMPL->utfEmoji(NS2STD(locale), detailed);
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

- (Emojidex_Data_Collection*)extendedEmoji
{
  const Emojidex::Data::Collection& tmp = IMPL->extendedEmoji();
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

- (Emojidex_Data_Collection*)extendedEmoji:(NSString*)locale
{
  const Emojidex::Data::Collection& tmp = IMPL->extendedEmoji(NS2STD(locale));
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

- (Emojidex_Data_Collection*)extendedEmoji:(NSString*)locale detailed:(BOOL)detailed
{
  const Emojidex::Data::Collection& tmp = IMPL->extendedEmoji(NS2STD(locale), detailed);
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

+ (Emojidex_Data_Collection*)nextPage:(Emojidex_Data_Collection*)collection
{
  const Emojidex::Data::Collection& tmp = *[collection getImpl];
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

- (Emojidex_Data_Collection*)emoji
{
  const Emojidex::Data::Collection& tmp = IMPL->emoji();
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

- (Emojidex_Data_Collection*)emoji:(unsigned int)page
{
  const Emojidex::Data::Collection& tmp = IMPL->emoji(page);
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

- (Emojidex_Data_Collection*)emoji:(unsigned int)page limit:(unsigned int)limit
{
  const Emojidex::Data::Collection& tmp = IMPL->emoji(page, limit);
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

- (Emojidex_Data_Collection*)emoji:(unsigned int)page limit:(unsigned int)limit detailed:(BOOL)detailed
{
  const Emojidex::Data::Collection& tmp = IMPL->emoji(page, limit, detailed);
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

- (Emojidex_Data_Collection*)newest:(NSString*)authToken
{
  const Emojidex::Data::Collection& tmp = IMPL->newest(NS2STD(authToken));
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

- (Emojidex_Data_Collection*)newest:(NSString*)authToken page:(unsigned int)page
{
  const Emojidex::Data::Collection& tmp = IMPL->newest(NS2STD(authToken), page);
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

- (Emojidex_Data_Collection*)newest:(NSString*)authToken page:(unsigned int)page limit:(unsigned int)limit
{
  const Emojidex::Data::Collection& tmp = IMPL->newest(NS2STD(authToken), page, limit);
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

- (Emojidex_Data_Collection*)newest:(NSString*)authToken page:(unsigned int)page limit:(unsigned int)limit detailed:(BOOL)detailed
{
  const Emojidex::Data::Collection& tmp = IMPL->newest(NS2STD(authToken), page, limit, detailed);
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

- (Emojidex_Data_Collection*)popular:(NSString*)authToken
{
  const Emojidex::Data::Collection& tmp = IMPL->popular(NS2STD(authToken));
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

- (Emojidex_Data_Collection*)popular:(NSString*)authToken page:(unsigned int)page
{
  const Emojidex::Data::Collection& tmp = IMPL->popular(NS2STD(authToken), page);
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

- (Emojidex_Data_Collection*)popular:(NSString*)authToken page:(unsigned int)page limit:(unsigned int)limit
{
  const Emojidex::Data::Collection& tmp = IMPL->popular(NS2STD(authToken), page, limit);
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

- (Emojidex_Data_Collection*)popular:(NSString*)authToken page:(unsigned int)page limit:(unsigned int)limit detailed:(BOOL)detailed
{
  const Emojidex::Data::Collection& tmp = IMPL->popular(NS2STD(authToken), page, limit, detailed);
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

@end
