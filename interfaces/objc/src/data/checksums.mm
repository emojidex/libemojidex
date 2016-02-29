
#import "checksums.h"
#import "checksums+private.h"

#import "../utils+private.h"

typedef Emojidex::Data::Checksums ImplType;
#define IMPL ((ImplType*)_impl)

@implementation Emojidex_Data_Checksums (Private)

- (id)initWithChecksums:(const Emojidex::Data::Checksums&)src
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

- (const Emojidex::Data::Checksums*)getImpl
{
  return IMPL;
}

@end

@implementation Emojidex_Data_Checksums

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

- (NSString*)sum:(NSString*)formatCode sizeCode:(NSString*)sizeCode
{
  return STD2NS(IMPL->sum(NS2STD(formatCode), NS2STD(sizeCode)));
}

- (void)setSvg:(NSString*)svg
{
  IMPL->svg = NS2STD(svg);
}

- (NSString*)getSvg
{
  return STD2NS(IMPL->svg);
}

@end
