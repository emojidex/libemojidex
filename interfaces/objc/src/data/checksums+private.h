
#import "../../../src/data/checksums.h"

@interface Emojidex_Data_Checksums (Private)

- (id)initWithChecksums:(const Emojidex::Data::Checksums&)src;

- (const Emojidex::Data::Checksums*)getImpl;

@end
