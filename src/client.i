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
#include "service/settings.h"
#include "service/transactor.h"
%}

// Ignore function pointer.
%ignore Emojidex::Data::Collection::moreMethod;
%ignore Emojidex::Data::Collection::setPagination;

// Ignore operator.
%ignore Emojidex::Data::Collection::operator<<;

// Ignore unordered_map.
%ignore Emojidex::Data::Collection::emoji;
%ignore Emojidex::Data::MojiCodes::moji_index;
%ignore Emojidex::Data::Checksums::png;
%ignore Emojidex::Service::Transactor::queryTemplate;
%ignore Emojidex::Service::Transactor::get;

// Include header files.
// Prototype.
namespace Emojidex {
  namespace Service {
    class Indexes;
    class Search;
    class Settings;
    class Transactor;
  }
  namespace Data {
    class Collection;
    class MojiCodes;
    class Emoji;
    class Checksums;
  }
  class Client;
}

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
      std::string moji;
      std::string code;
      std::string unicode;
      std::string category;
      std::vector<std::string> tags;
      std::string base;
      std::vector<std::string> variants;
      std::string link;
      // detailed
      bool is_wide;
      bool copyright_lock;
      int times_used;
      std::string attribution;
      std::string user_id;
      Checksums checksums;
    };
  }
}

// %include "data/checksums.h"
namespace Emojidex {
  namespace Data {
    class Checksums
    {
    public:
      std::string svg;
      Data::UnorderedMap <std::string, std::string> png;

      std::string sum(std::string format_code, std::string size_code);
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

      Data::UnorderedMap<std::string, Emojidex::Data::Emoji> emoji;

      //=====================================================================================
      // Broken out operations on the emoji map (for interfaces or implementations 
      // without map functionality)
      // ============

      // Returns a vector array of all emoji in the collection
      std::vector<Emojidex::Data::Emoji> all();

      // Adds an emoji to the map
      Emojidex::Data::Emoji add(Emojidex::Data::Emoji new_emoji);

      // Finds by moji[character]code (UTF emoji only)
      Emojidex::Data::Emoji findByMoji(std::string moji);
      // Finds by emoji [short] code
      Emojidex::Data::Emoji findByCode(std::string code);
      // Finds by Unicode value
      // *Unicode value must be lower case
      Emojidex::Data::Emoji findByUnicode(std::string unicode);

      //Emojidex::Data::Collection search()
      Emojidex::Data::Collection category(std::string category);

      // Merge a collection with this collection, overwriting emoji with the same
      // code in this collection. Rerturns this collection after the merge for chaining.
      Emojidex::Data::Collection merge(Emojidex::Data::Collection delta_collection);
      Emojidex::Data::Collection operator<<(Emojidex::Data::Collection delta_collection);
      
      //=====================================================================================
      // Service Info
      // ============
      std::string endpoint;
      bool detailed;
      std::string locale;
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
      std::string locale = "";
      std::string moji_string;
      std::vector<std::string> moji_array;
      Data::UnorderedMap<std::string, std::string> moji_index;
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
      Emojidex::Data::Collection term(std::string term);
    };
  }
}

// %include "service/settings.h"
namespace Emojidex {
  namespace Service {
    class Settings
    {
    public:
      static bool        initialized;
      static std::string api_host;
      static std::string api_prefix;
      static std::string api_protocol;
      static std::string cdn_host;
      static std::string cdn_prefix;
      static std::string cdn_protocol;
      static bool        closed_net;
      static std::string token;
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
      std::string generateQueryString(Data::UnorderedMap<std::string, std::string> query);
      boost::asio::ssl::stream<boost::asio::ip::tcp::socket>* getStream();
    public:
      Transactor();

      Data::UnorderedMap<std::string, std::string> queryTemplate(bool defaults = true);

      std::string get(std::string endpoint, Data::UnorderedMap<std::string, std::string> query = {{"", ""}});
    };
  }
}

// Include sub interface files.
%include "service/indexes.i"

// Rename template classes.
%template(StringVector) std::vector<std::string>;
%template(EmojiVector) std::vector<Emojidex::Data::Emoji>;
