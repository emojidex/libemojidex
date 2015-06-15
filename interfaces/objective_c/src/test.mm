
#import "test.h"
#import <Foundation/NSObject.h>
#import "../../../src/client.h"

@implementation Hoge
- (void)foo
{
  Emojidex::Client client;
  NSLog(@"hoge: %d\n", client.apiVersion());
}
@end
