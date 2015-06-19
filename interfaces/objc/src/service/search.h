
#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>

#import "../data/collection.h"

@interface Emojidex_Service_Search : NSObject
{
@private
  void* _impl;
  BOOL _autoDelete;
}

- (id)init;
- (void)dealloc;

// Emojidex::Data::Collection term(std::string term);
- (Emojidex_Data_Collection*)term:(NSString*)term;

// unsigned int current_page;
- (void)setCurrentPage:(unsigned int)currentPage;
- (unsigned int)getCurrentPage;

@end
