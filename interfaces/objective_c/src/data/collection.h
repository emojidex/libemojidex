
#import <Foundation/NSObject.h>

@interface Emojidex_Data_Collection : NSObject
{
@private
  void* _impl;
  BOOL _autoDelete;
}

- (id)init;
- (void)dealloc;

@end
