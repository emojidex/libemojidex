
#import "../../../src/data/emoji.h"

@interface Emojidex_Data_Emoji (Private)

- (id)initWithEmoji:(const Emojidex::Data::Emoji&)src;

- (const Emojidex::Data::Emoji*)getImpl;

@end
