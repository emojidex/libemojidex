%module(package="Emojidex:::Data") "Emojidex::Data::Collection"

%nspace Emojidex::Data::Collection;

%include <std_string.i>

// For java.
SWIG_JAVABODY_PROXY(public, public, SWIGTYPE)
SWIG_JAVABODY_TYPEWRAPPER(public, public, public, SWIGTYPE)
%typemap(javaimports) Emojidex::Data::Collection %{
import com.emojidex.libemojidex.EmojiVector;
%}

%{
#include "data/collection.h"
%}

// Ignore operator overrides
%ignore Emojidex::Data::Collection::operator<<;

// Ignore function pointers
%ignore Emojidex::Data::Collection::moreMethod;
%ignore Emojidex::Data::Collection::setPagination;

// Ignore std::unordered_map
%ignore Emojidex::Data::Collection::emoji;

// %include "data/collection.h"
namespace Emojidex {
  namespace Data {
    //! A managed collection of emoji objects
    class Collection
    {
    private:
      // Called when more() is invoked.
      // Results are combined into this collection but a collection with just the new results 
      // is returned.
      Collection (*moreMethod)(Emojidex::Data::Collection);

      void fillEmojiFromJSON(rapidjson::Value& d);
      void fillEmojiFromMsgPack(const msgpack::object& d);

      Collection genericMore();
    public:
      Collection();
      ~Collection();

      //! emoji data hash, mapped by code
      std::unordered_map<std::string, Emojidex::Data::Emoji> emoji;

      //=====================================================================================
      // Broken out operations on the emoji map (for interfaces or implementations 
      // without map functionality)
      // ============

      //! Returns a vector array of all emoji in the collection
      std::vector<Emojidex::Data::Emoji> all();

      //! Adds an emoji to the map
      Emojidex::Data::Emoji add(Emojidex::Data::Emoji new_emoji);

      //! Removes an emoji from the map [by code]
      /*!
       * Returns true if the emoji was located in the map and removed
       * Returns false if the emoji was not located in the map
       */
      bool remove(std::string code);

      //! Finds by moji[character]code (UTF emoji only)
      Emojidex::Data::Emoji findByMoji(std::string moji);
      //! Finds by emoji [short] code
      Emojidex::Data::Emoji findByCode(std::string code);
      //! Finds by Unicode value (must be lower case)
      Emojidex::Data::Emoji findByUnicode(std::string unicode);

      //! Obtain a sub collection of emoji of the specified category
      Emojidex::Data::Collection category(std::string category);

      //! Merge a collection with this collection.
      /*!
       * Overwrites emoji with the same code.
       * Rerturns the joined collection after the merge for chaining.
       */
      Emojidex::Data::Collection* merge(Emojidex::Data::Collection delta_collection);
      Emojidex::Data::Collection* operator<<(Emojidex::Data::Collection delta_collection);

      //! Add emoji from a JSON string
      //! Returns this collection after the merge for chaining.
      Emojidex::Data::Collection* mergeJSON(std::string json_string);

      //! Add emoji from a msgpack string
      //! Returns this collection after the merge for chaining.
      Emojidex::Data::Collection* mergeMsgPack(std::string msgpack_string);

      //=====================================================================================
      // Service Info
      // ============
      
      //! The service endpoint this collection is derived from 
      std::string endpoint;
      //! Query options on the endpoint
      Emojidex::Service::QueryOpts opts;

      //! The total number of emoji availble on the service to fill this collection
      unsigned int total_count;

      //! Get more of the collection if the collection is paginated and has remaining pages.
      /*!
       * Returns true if the next page was sucessfully obtained. Returns false if there are no 
       * more pages/emoji to obtain.
       */
      Emojidex::Data::Collection more();

      //! Sets up collection as a paged collection (with more pages/emoji on the service).
      void setPagination(Collection (*moreMethod)(Emojidex::Data::Collection), 
        unsigned int starting_page, unsigned int limit, bool detailed);
    };
  }
}

// Rename template classes.
#ifndef TEMPLATE_EMOJI_VECTOR
#define TEMPLATE_EMOJI_VECTOR
%template(EmojiVector) std::vector<Emojidex::Data::Emoji>;
#endif
