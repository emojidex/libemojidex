
#import "client.h"

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

@end
