#ifndef EMOJIDEX_SERVICE_SEARCH_CONDITIONS_H
#define EMOJIDEX_SERVICE_SEARCH_CONDITIONS_H

#include <vector>
#include <string>
#include <unordered_map>

#define DEFAULT_LOCALE "en"
#define DEFAULT_PAGE 1
#define DEFAULT_LIMIT 50
#define TF(bv) ((bv)?"true":"false")

namespace Emojidex {
  namespace Service {
	//! Portable class to set complex query options
	/*!
	 * This class was introduced in libemojidex to combat several issues.
	 * Primarily, it's here to be an easy-to-use interface to set things like
	 * hashes and maps in any language an interface is availbe in. It's also 
	 * here to offer a lot of flexibility in query customization without having 
	 * to add a lot of arguments to every method. Not all opts have a functionality 
	 * on all endpoints, but the ones that do not will simply be discarded.
	 *
	 * Any option that, if included, could change the results of the query is 
	 * not set during a get nor is it intialized by default to any value. 
	 */
    class QueryOpts
    {
      private:
      std::string _locale;
      unsigned int _page;
      unsigned int _limit;
      bool _detailed;
      std::string _username;
      std::string _auth_token;
      std::vector<std::string> _tags;
      std::vector<std::string> _categories;
      std::string _sort;

      // Opts string that is appended to the end of a query
      std::string _ext_opts;

      public:
      QueryOpts();

      //! Sets defaults for a generic collection
      void setCollectionDefaults();

      //! Chain method to set "locale"
      Emojidex::Service::QueryOpts& locale(const std::string &locale = DEFAULT_LOCALE);
      //! Gets current value of "locale" or returns default of "en" if not set
      /*!
	   * DOES NOT set value of "locale" if locale is not set
	   */
      const std::string& getLocale() const;

      //! Chain method to set "page" by unsigned int
      Emojidex::Service::QueryOpts& page(unsigned int number = DEFAULT_PAGE);
      //! Gets current value of "page" or returns default of 1 if not set
      /*!
	   * DOES NOT set value of "page" if page is not set
	   */
      unsigned int getPage() const;

      //! Chain method to set "limit" by unsigned int
      Emojidex::Service::QueryOpts& limit(unsigned int value = DEFAULT_LIMIT);
      //! Gets current value of "limit" or returns default (50) if not set
      /*!
	   * DOES NOT set value of "limit" if limit is not set
	   */
      unsigned int getLimit() const;

      //! Chain method to set "detailed" by bool
      Emojidex::Service::QueryOpts& detailed(bool detail = true);
      //! Gets current value of "detailed" or returns true if not set
      /*!
	   * DOES NOT set value of "detailed" if detailed is not set
	   */
      bool getDetailed() const;

      //! Chain method to set "username"
      Emojidex::Service::QueryOpts& username(const std::string &username = "");
      //! Gets current value of "username" or returns empty string if not set
      /*!
	   * DOES NOT set value of "username" if username is not set
	   */
      const std::string& getUsername() const;

      //! Chain method to set "auth_token"
      Emojidex::Service::QueryOpts& auth_token(const std::string &auth_token = "");
      //! Gets current value of "auth_token" or returns empty string if not set
      /*!
	   * DOES NOT set value of "auth_token" if username is not set
	   */
      const std::string& getAuthToken() const;

      //! Chain method to add a tag string to the tags vector
      Emojidex::Service::QueryOpts& tag(const std::string &tag);
      //! Clear current value of "tags"
      Emojidex::Service::QueryOpts& clearTags();
      //! Gets current value of "tags" or returns empty vector if not set
      /*!
	   * DOES NOT set value of "tags" if tags is not set
	   */
      const std::vector<std::string>& getTags() const;

      //! Chain method to add a category string to the categories vector
      Emojidex::Service::QueryOpts& category(const std::string &category);
      //! Clear current value of "categories"
      Emojidex::Service::QueryOpts& clearCategories();
      //! Gets current value of "categories" or returns empty vector if not set
      /*!
	   * DOES NOT set value of "categories" if categories is not set
	   */
      const std::vector<std::string>& getCategories() const;

      //! Sets sort order
      Emojidex::Service::QueryOpts& setSort(std::string order = "");

      //! Adds an opt to the ext_opts string with a prefixed "&" (or custom prefix when specified)
      Emojidex::Service::QueryOpts& ext(const std::string &opt, const std::string &prefix = "&");
      //! Clear ext opts string
      Emojidex::Service::QueryOpts& clearExt();
      //! Get ext opt string
      const std::string& getExt() const;


	  //! Feed an unordered map into opts
      Emojidex::Service::QueryOpts& parseUnorderedMap(const std::unordered_map<std::string, std::string> &source_map);

	  //! Provides current query opt set as a single string
      std::string to_string() const;
    };
  }
}

#endif /* EMOJIDEX_SERVICE_SEARCH_CONDITIONS_H */
