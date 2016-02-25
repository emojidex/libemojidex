
#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>

#import "query_opts.h"
#import "../data/collection.h"

@interface Emojidex_Service_Search : NSObject
{
@private
  void* _impl;
  BOOL _autoDelete;
}

- (id)init;
- (void)dealloc;

// Emojidex::Data::Collection term(const std::string code_cont, Emojidex::Service::QueryOpts *conditions = NULL);
- (Emojidex_Data_Collection*)term:(NSString*)codeCont;
- (Emojidex_Data_Collection*)term:(NSString*)codeCont conditions:(Emojidex_Service_QueryOpts*)conditions;


// Attempts to directly obtain emoji data by code
// Returns a Data::Emoji object filled with the emoji info on success (the emoji is registered)
// Returns an empty emoji object with only the code field filled on failure (the emoji is not registered)
- (Emojidex_Data_Emoji*)find:(NSString*)code;
- (Emojidex_Data_Emoji*)find:(NSString*)code detailed:(BOOL)detailed;

// unsigned int current_page;
- (void)setCurrentPage:(unsigned int)currentPage;
- (unsigned int)getCurrentPage;

@end
