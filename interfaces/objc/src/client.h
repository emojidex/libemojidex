
#import <Foundation/NSObject.h>

#import "service/search.h"

@interface Emojidex_Client : NSObject
{
@private
  void* _impl;
  BOOL _autoDelete;
}

- (id)init;
- (void)dealloc;

- (char)apiVersion;

// Emojidex::Service::Search *Search;
- (void)setSearch:(Emojidex_Service_Search*)search;
- (Emojidex_Service_Search*)getSearch;

// Emojidex::Service::Search *Indexes;
- (void)setIndexes:(Emojidex_Service_Search*)search;
- (Emojidex_Service_Search*)getIndexes;

@end
