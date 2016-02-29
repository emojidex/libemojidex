
#import "query_opts.h"
#import "query_opts+private.h"

#import "../utils+private.h"

typedef Emojidex::Service::QueryOpts ImplType;
#define IMPL ((ImplType*)_impl)

@implementation Emojidex_Service_QueryOpts (Private)

- (id)initWithQueryOpts:(Emojidex::Service::QueryOpts&)src
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

- (Emojidex::Service::QueryOpts*)getImpl
{
  return IMPL;
}

@end

@implementation Emojidex_Service_QueryOpts

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

- (void)setCollectionDefaults
{
  IMPL->setCollectionDefaults();
}

- (Emojidex_Service_QueryOpts*)locale
{
  IMPL->locale();
  return self;
}

- (Emojidex_Service_QueryOpts*)locale:(NSString*)locale
{
  IMPL->locale(NS2STD(locale));
  return self;
}

- (NSString*)getLocale
{
  return STD2NS(IMPL->getLocale());
}

- (Emojidex_Service_QueryOpts*)page
{
  IMPL->page();
  return self;
}

- (Emojidex_Service_QueryOpts*)page:(unsigned int)number
{
  IMPL->page(number);
  return self;
}

- (unsigned int)getPage
{
  return IMPL->getPage();
}

- (Emojidex_Service_QueryOpts*)limit
{
  IMPL->limit();
  return self;
}

- (Emojidex_Service_QueryOpts*)limit:(unsigned int)value
{
  IMPL->limit(value);
  return self;
}

- (unsigned int)getLimit
{
  return IMPL->getLimit();
}

- (Emojidex_Service_QueryOpts*)detailed
{
  IMPL->detailed();
  return self;
}

- (Emojidex_Service_QueryOpts*)detailed:(BOOL)detail
{
  IMPL->detailed(detail);
  return self;
}

- (BOOL)getDetailed
{
  return IMPL->getDetailed();
}

- (Emojidex_Service_QueryOpts*)username
{
  IMPL->username();
  return self;
}

- (Emojidex_Service_QueryOpts*)username:(NSString*)username
{
  IMPL->username(NS2STD(username));
  return self;
}

- (NSString*)getUsername
{
  return STD2NS(IMPL->getUsername());
}

- (Emojidex_Service_QueryOpts*)authToken
{
  IMPL->auth_token();
  return self;
}

- (Emojidex_Service_QueryOpts*)authToken:(NSString*)authToken
{
  IMPL->auth_token(NS2STD(authToken));
  return self;
}

- (NSString*)getAuthToken
{
  return STD2NS(IMPL->getAuthToken());
}

- (Emojidex_Service_QueryOpts*)tag:(NSString*)tag
{
  IMPL->tag(NS2STD(tag));
  return self;
}

- (Emojidex_Service_QueryOpts*)clearTags
{
  IMPL->clearTags();
  return self;
}

- (NSArray*)getTags
{
  NSMutableArray* newArray = [NSMutableArray array];
  const std::vector<std::string>& src = IMPL->getTags();
  const size_t size = src.size();
  for(size_t i = 0;  i < size;  ++i)
    [newArray addObject:STD2NS(src[i])];
  return [newArray copy];
}

- (Emojidex_Service_QueryOpts*)category:(NSString*)category
{
  IMPL->category(NS2STD(category));
  return self;
}

- (Emojidex_Service_QueryOpts*)clearCategories
{
  IMPL->clearCategories();
  return self;
}

- (NSArray*)getCategories
{
  NSMutableArray* newArray = [NSMutableArray array];
  const std::vector<std::string>& src = IMPL->getCategories();
  const size_t size = src.size();
  for(size_t i = 0;  i < size;  ++i)
    [newArray addObject:STD2NS(src[i])];
  return [newArray copy];
}

- (Emojidex_Service_QueryOpts*)ext:(NSString*)opt
{
  IMPL->ext(NS2STD(opt));
  return self;
}

- (Emojidex_Service_QueryOpts*)ext:(NSString*)opt prefix:(NSString*)prefix
{
  IMPL->ext(NS2STD(opt), NS2STD(prefix));
  return self;
}

- (Emojidex_Service_QueryOpts*)clearExt
{
  IMPL->clearExt();
  return self;
}

- (NSString*)getExt
{
  return STD2NS(IMPL->getExt());
}

- (NSString*)toString
{
  return STD2NS(IMPL->to_string());
}

@end
