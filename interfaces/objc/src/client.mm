
#import "client.h"

#import "service/search+private.h"
#import "service/indexes+private.h"

#import "../../../src/client.h"

typedef Emojidex::Client ImplType;
#define IMPL ((ImplType*)_impl)

@implementation Emojidex_Client

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

- (char)apiVersion
{
  return IMPL->apiVersion();
}

- (void)setSearch:(Emojidex_Service_Search*)search
{
  IMPL->Search = [search getImpl];
}

- (Emojidex_Service_Search*)getSearch
{
  return [[[Emojidex_Service_Search alloc] initWithSearch:IMPL->Search] autorelease];
}

- (void)setIndexes:(Emojidex_Service_Indexes*)indexes
{
  IMPL->Indexes = [indexes getImpl];
}

- (Emojidex_Service_Indexes*)getIndexes
{
  return [[[Emojidex_Service_Indexes alloc] initWithIndexes:IMPL->Indexes] autorelease];
}

@end
