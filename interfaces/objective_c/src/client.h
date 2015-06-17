
#import <Foundation/NSObject.h>

@interface Emojidex_Client : NSObject
{
@private
  void* _impl;
  BOOL _autoDelete;
}

- (id)init;
- (void)dealloc;
- (char)apiVersion;

@end
