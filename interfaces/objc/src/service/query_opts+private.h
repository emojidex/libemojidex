
#import "../../../src/service/query_opts.h"

@interface Emojidex_Service_QueryOpts (Private)

- (id)initWithQueryOpts:(Emojidex::Service::QueryOpts&)src;

- (Emojidex::Service::QueryOpts*)getImpl;

@end
