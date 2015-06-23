
#import "../../../src/service/search.h"

@interface Emojidex_Service_Search (Private)

- (id)initWithSearch:(Emojidex::Service::Search*)src;

- (Emojidex::Service::Search*)getImpl;

@end
