
#import <Foundation/NSString.h>

#import "data.h"

@interface Libemojidex

// const char encapsulator = ':';
+ (NSString*)encapsulator;

// std::string escapeCode(std::string code);
+ (NSString*)escapeCode:(NSString*)code;

// std::string unescapeCode(std::string code);
+ (NSString*)unescapeCode:(NSString*)code;

// std::string encapsulateCode(std::string code);
+ (NSString*)encapsulateCode:(NSString*)code;

// std::string unencapsulateCode(std::string code);
+ (NSString*)unencapsulateCode:(NSString*)code;

@end