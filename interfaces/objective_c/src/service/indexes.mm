
#import "indexes.h"
#import "../data/moji_codes_private.h"
#import "../data/collection_private.h"
#import "../utils_private.h"

#import "../../../src/service/indexes.h"

typedef Emojidex::Service::Indexes ImplType;
#define IMPL ((ImplType*)_impl)

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
  return [[[Emojidex_Data_MojiCodes alloc] initWithInstance:IMPL->mojiCodes()] autorelease];
}

- (Emojidex_Data_MojiCodes*)mojiCodes:(NSString*)locale
{
  return [[[Emojidex_Data_MojiCodes alloc] initWithInstance:IMPL->mojiCodes(NS2STD(locale))] autorelease];
}

// - (Emojidex_Data_Collection*)utfEmoji
// {
//   return [[[Emojidex_Data_Collection alloc] initWithInstance:IMPL->utfEmoji()] autorelease];
// }

// - (Emojidex_Data_Collection*)utfEmoji:(NSString*)locale
// {
//   return nil;//[[[Emojidex_Data_Collection alloc] initWithInstance:IMPL->utfEmoji(NS2STD(locale))] autorelease];
// }

// - (Emojidex_Data_Collection*)utfEmoji:(NSString*)locale detailed:(BOOL)detailed
// {
//   return nil;
// }

@end
