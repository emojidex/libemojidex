
#import "search.h"

#import "../../../src/service/search.h"

typedef Emojidex::Service::Search ImplType;
#define IMPL ((ImplType*)_impl)

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

@end
