
#import "moji_codes.h"
#import "moji_codes+private.h"
#import "../utils+private.h"

typedef Emojidex::Data::MojiCodes ImplType;
#define IMPL ((ImplType*)_impl)

@implementation Emojidex_Data_MojiCodes (Private)

- (id)initWithMojiCodes:(const Emojidex::Data::MojiCodes&)src
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

@end

@implementation Emojidex_Data_MojiCodes

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

- (void)setLocale:(NSString*)locale
{
  IMPL->locale = NS2STD(locale);
}

- (NSString*)getLocale
{
  return STD2NS(IMPL->locale);
}

- (void)setMojiString:(NSString*)mojiString
{
  IMPL->moji_string = [mojiString UTF8String];
}

- (NSString*)getMojiString
{
  return [NSString stringWithUTF8String:IMPL->moji_string.c_str()];
}

- (void)setMojiArray:(NSArray*)mojiArray
{
  IMPL->moji_array.clear();
  const int size = [mojiArray count];
  for(int i = 0;  i < size;  ++i)
    IMPL->moji_array.push_back(NS2STD([mojiArray objectAtIndex:i]));
}

- (NSArray*)getMojiArray
{
  NSMutableArray* newArray = [NSMutableArray array];
  const size_t size = IMPL->moji_array.size();
  for(size_t i = 0;  i < size;  ++i)
    [newArray addObject:STD2NS(IMPL->moji_array[i])];
  return [newArray copy];
}

@end
