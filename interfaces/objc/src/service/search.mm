
#import "search.h"
#import "search+private.h"

#import "query_opts+private.h"
#import "../data/emoji+private.h"
#import "../data/collection+private.h"
#import "../utils+private.h"

typedef Emojidex::Service::Search ImplType;
#define IMPL ((ImplType*)_impl)

@implementation Emojidex_Service_Search (Private)

- (id)initWithSearch:(Emojidex::Service::Search*)src
{
  self = [super init];
  if(self != nil)
  {
    _impl = src;
  }
  _autoDelete = NO;
  return self;
}

- (Emojidex::Service::Search*)getImpl
{
  return IMPL;
}

@end

@implementation Emojidex_Service_Search

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

- (Emojidex_Data_Collection*)term:(NSString*)codeCont
{
  const Emojidex::Data::Collection& tmp = IMPL->term(NS2STD(codeCont));
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

- (Emojidex_Data_Collection*)term:(NSString*)codeCont conditions:(Emojidex_Service_QueryOpts*)conditions
{
  const Emojidex::Data::Collection& tmp = IMPL->term(NS2STD(codeCont), [conditions getImpl]);
  return [[[Emojidex_Data_Collection alloc] initWithCollection:tmp] autorelease];
}

- (Emojidex_Data_Emoji*)find:(NSString*)code
{
  const Emojidex::Data::Emoji& tmp = IMPL->find(NS2STD(code));
  return [[[Emojidex_Data_Emoji alloc] initWithEmoji:tmp] autorelease];
}

- (Emojidex_Data_Emoji*)find:(NSString*)code detailed:(BOOL)detailed
{
  const Emojidex::Data::Emoji& tmp = IMPL->find(NS2STD(code), detailed);
  return [[[Emojidex_Data_Emoji alloc] initWithEmoji:tmp] autorelease];
}

- (void)setCurrentPage:(unsigned int)currentPage
{
  IMPL->current_page = currentPage;
}

- (unsigned int)getCurrentPage
{
  return IMPL->current_page;
}

@end
