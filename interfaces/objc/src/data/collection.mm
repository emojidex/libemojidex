
#import "collection.h"
#import "collection+private.h"
#import "emoji+private.h"

#import "../utils+private.h"

typedef Emojidex::Data::Collection ImplType;
#define IMPL ((ImplType*)_impl)

@implementation Emojidex_Data_Collection (Private)

- (id)initWithCollection:(const Emojidex::Data::Collection&)src
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

- (const Emojidex::Data::Collection*) getImpl
{
  return IMPL;
}

@end

@implementation Emojidex_Data_Collection

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

- (NSArray*)all
{
  NSMutableArray* newArray = [NSMutableArray array];
  const std::vector<Emojidex::Data::Emoji>& src = IMPL->all();
  const size_t size = src.size();
  for(size_t i = 0;  i < size;  ++i)
  {
    Emojidex_Data_Emoji* emoji = [[[Emojidex_Data_Emoji alloc] initWithEmoji:src[i]] autorelease];
    [newArray addObject:emoji];
  }
  return [newArray copy];
}

- (Emojidex_Data_Emoji*)add:(Emojidex_Data_Emoji*)newEmoji
{
  const Emojidex::Data::Emoji& tmp = IMPL->add(*[newEmoji getImpl]);
  return [[[Emojidex_Data_Emoji alloc] initWithEmoji:tmp] autorelease];
}

- (Emojidex_Data_Emoji*)findByMoji:(NSString*)moji
{
  const Emojidex::Data::Emoji& tmp = IMPL->findByMoji(NS2STD(moji));
  return [[[Emojidex_Data_Emoji alloc] initWithEmoji:tmp] autorelease];
}

- (Emojidex_Data_Emoji*)findByCode:(NSString*)code
{
  const Emojidex::Data::Emoji& tmp = IMPL->findByCode(NS2STD(code));
  return [[[Emojidex_Data_Emoji alloc] initWithEmoji:tmp] autorelease];
}

- (Emojidex_Data_Emoji*)findByUnicode:(NSString*)unicode
{
  const Emojidex::Data::Emoji& tmp = IMPL->findByUnicode(NS2STD(unicode));
  return [[[Emojidex_Data_Emoji alloc] initWithEmoji:tmp] autorelease];
}

- (Emojidex_Data_Collection*)category:(NSString*)category
{
  const Emojidex::Data::Collection& tmp = IMPL->category(NS2STD(category));
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

- (Emojidex_Data_Collection*)merge:(Emojidex_Data_Collection*)deltaCollection
{
  IMPL->merge(*((ImplType*)deltaCollection->_impl));
  return self;
}

- (void)setEndpoint:(NSString*)endpoint
{
  IMPL->endpoint = NS2STD(endpoint);
}

- (NSString*)getEndpoint
{
  return STD2NS(IMPL->endpoint);
}

- (void)setDetailed:(BOOL)detailed
{
  IMPL->detailed = detailed;
}

- (BOOL)getDetailed
{
  return IMPL->detailed;
}

- (void)setLocale:(NSString*)locale
{
  IMPL->locale = NS2STD(locale);
}

- (NSString*)getLocale
{
  return STD2NS(IMPL->locale);
}

- (void)setPage:(unsigned int)page
{
  IMPL->page = page;
}

- (unsigned int)getPage
{
  return IMPL->page;
}

- (void)setLimit:(unsigned short)limit
{
  IMPL->limit = limit;
}

- (unsigned short)getLimit
{
  return IMPL->limit;
}

- (void)setTotalCount:(unsigned int)totalCount
{
  IMPL->total_count = totalCount;
}

- (unsigned int)getTotalCount
{
  return IMPL->total_count;
}

- (Emojidex_Data_Collection*)more
{
  const Emojidex::Data::Collection& tmp = IMPL->more();
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

@end
