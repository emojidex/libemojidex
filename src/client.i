%module emojidex

// Include STL header files.
%include "std_string.i"
%include "std_vector.i"

// For java.
%pragma(java) jniclasscode=%{
  static
  {
    NativeLibLoader.load();
  }
%}

// 
%{
#include "client.h"
%}

// Ignore function pointer.
%ignore Emojidex::Data::Collection::moreMethod;
%ignore Emojidex::Data::Collection::setPagination;

// Ignore operator.
%ignore Emojidex::Data::Collection::operator<<;

// Ignore unordered_map.
%ignore Emojidex::Data::Collection::emoji;
%ignore Emojidex::Data::MojiCodes::moji_index;
%ignore Emojidex::Service::Transactor::queryTemplate;
%ignore Emojidex::Service::Transactor::get;

// Include header files.
// %include "client.h"
namespace Emojidex {
  // Core client class (includes all components in a central state-machine client)
  class Client
  {
  private:
    //Emojidex::Transactor *transactor;
  public:
    Emojidex::Service::Search *Search;
    Emojidex::Service::Search *Indexes;

    Client();
    char apiVersion();
  }; // Client
} // Emojidex namespace

// %include "data/emoji.h"
namespace Emojidex {
  namespace Data {
    // emoji base data
    class Emoji
    {
    public:
      string moji;
      string code;
      string unicode;
      string category;
      bool is_wide;
      vector<string> tags;
      string base;
      vector<string> variants;

      string author;
      string link;
    };
  }
}

// %include "data/collection.h"
namespace Emojidex {
  namespace Data {
    // emoji base data
    class Collection
    {
    private:
      // Called when more() is invoked.
      // Results are combined into this collection but a collection with just the new results 
      // is returned.
      Emojidex::Data::Collection (*moreMethod)(Emojidex::Data::Collection);
    public:
      Collection();
      ~Collection();

      unordered_map<string, Emojidex::Data::Emoji> emoji;

      //=====================================================================================
      // Broken out operations on the emoji map (for interfaces or implementations 
      // without map functionality)
      // ============

      // Returns a vector array of all emoji in the collection
      vector<Emojidex::Data::Emoji> all();

      // Adds an emoji to the map
      Emojidex::Data::Emoji add(Emojidex::Data::Emoji new_emoji);

      // Finds by moji[character]code (UTF emoji only)
      Emojidex::Data::Emoji findByMoji(string moji);
      // Finds by emoji [short] code
      Emojidex::Data::Emoji findByCode(string code);
      // Finds by Unicode value
      // *Unicode value must be lower case
      Emojidex::Data::Emoji findByUnicode(string unicode);

      //Emojidex::Data::Collection search()
      Emojidex::Data::Collection category(string category);

      // Merge a collection with this collection, overwriting emoji with the same
      // code in this collection. Rerturns this collection after the merge for chaining.
      Emojidex::Data::Collection merge(Emojidex::Data::Collection delta_collection);
      Emojidex::Data::Collection operator<<(Emojidex::Data::Collection delta_collection);
      
      //=====================================================================================
      // Service Info
      // ============
      string endpoint;
      bool detailed;
      string locale;
      unsigned int page;
      unsigned short limit;
      unsigned int total_count;

      // Get more of the collection if the collection is paginated and has remaining pages.
      // Returns true if the next page was sucessfully obtained. Returns false if there are 
      // no more pages/emoji to obtain.
      Emojidex::Data::Collection more();

      // Sets up collection as a paged collection (with more pages/emoji remaining on the 
      // service).
      void setPagination(
          Emojidex::Data::Collection (*moreMethod)(Emojidex::Data::Collection), 
          unsigned int starting_page, unsigned int limit);
    };
  }
}

// %include "data/moji_codes.h"
namespace Emojidex {
  namespace Data {
    // Moji code container with 3 types of moji code indexes
    class MojiCodes
    {
    public:
      string locale = "";
      string moji_string;
      vector<string> moji_array;
      unordered_map<string, string> moji_index;
    };
  }
}

// %include "service/search.h"
namespace Emojidex {
  namespace Service {
    class Search
    {
    public:
      unsigned int current_page;

      Search();
      Emojidex::Data::Collection term(string term);
    };
  }
}

// %include "service/settings.h"
namespace Emojidex {
  namespace Service {
    class Settings
    {
    public:
      static bool initialized;
      static string api_host;
      static string api_prefix;
      static string api_protocol;
      static string cdn_host;
      static string cdn_prefix;
      static string cdn_protocol;
      static bool   closed_net;
      static string token;
    };
  }
}

// %include "service/transactor.h"
namespace Emojidex {
  namespace Service {
    // performs transactions with an emojidex API server
    class Transactor
    {
    private:
      string generateQueryString(unordered_map<string, string> query);
      boost::asio::ssl::stream<boost::asio::ip::tcp::socket>* getStream();
    public:
      Transactor();

      unordered_map<string, string> queryTemplate(bool defaults = true);

      string get(string endpoint, unordered_map<string, string> query = {{"", ""}});
    };
  }
}

// Include sub interface files.
%include "service/indexes.i"

// Rename template classes.
%template(StringVector) std::vector<std::string>;
%template(EmojiVector) std::vector<Emojidex::Data::Emoji>;
