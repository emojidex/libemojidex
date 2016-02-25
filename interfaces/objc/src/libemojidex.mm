
#import "libemojidex.h"

#import "utils+private.h"

#import "../../../src/libemojidex.h"

@implementation Libemojidex

+ (NSString*)encapsulator
{
  return [NSString stringWithFormat:@"%c", Emojidex::encapsulator];
}

+ (NSString*)escapeCode:(NSString*)code;
{
  return STD2NS(Emojidex::escapeCode(NS2STD(code)));
}

+ (NSString*)unescapeCode:(NSString*)code;
{
  return STD2NS(Emojidex::unescapeCode(NS2STD(code)));
}

+ (NSString*)encapsulateCode:(NSString*)code;
{
  return STD2NS(Emojidex::encapsulateCode(NS2STD(code)));
}

+ (NSString*)unencapsulateCode:(NSString*)code;
{
  return STD2NS(Emojidex::unencapsulateCode(NS2STD(code)));
}

@end