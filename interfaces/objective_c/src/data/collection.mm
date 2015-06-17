
#import "collection.h"
#import "collection_private.h"

typedef Emojidex::Data::Collection ImplType;
#define IMPL ((ImplType*)_impl)

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

- (id)initWithInstance:(const Emojidex::Data::Collection&)src
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
