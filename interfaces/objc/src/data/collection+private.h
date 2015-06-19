
#import "../../../src/data/collection.h"

@interface Emojidex_Data_Collection (Private)

- (id)initWithCollection:(const Emojidex::Data::Collection&)src;

- (const Emojidex::Data::Collection*) getImpl;

@end
