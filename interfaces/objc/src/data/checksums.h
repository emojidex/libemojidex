
#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>

@interface Emojidex_Data_Checksums : NSObject
{
@private
  void* _impl;
  BOOL _autoDelete;
}

- (id)init;
- (void)dealloc;

- (NSString*)sum:(NSString*)formatCode sizeCode:(NSString*)sizeCode;

// std::string svg;
- (void)setSvg:(NSString*)svg;
- (NSString*)getSvg;

// Data::UnorderedMap <std::string, std::string> png;
// - (void)setPng:(NSObject*)png;
// - (NSObject*)getPng;

@end
