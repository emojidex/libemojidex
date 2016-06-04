%module(package="Emojidex::Service") "Emojidex::Service::Search"

%nspace Emojidex::Service::Search;

%include <std_string.i>
%include <std_vector.i>

// For java.
%typemap(javaimports) Emojidex::Service::Search %{
import com.emojidex.libemojidex.StringVector;
%}

%{
#include "service/search.h"
%}

namespace Emojidex {
  namespace Service {
    class Search
    {
    private:
      const Emojidex::Service::User *user;

    public:
      unsigned int current_page;

      Search();

      void setUser(const Emojidex::Service::User *user);

      Emojidex::Data::Collection term(const std::string code_cont, Emojidex::Service::QueryOpts *conditions = NULL);
      Emojidex::Data::Collection starting(std::string code_sw, Emojidex::Service::QueryOpts *conditions = NULL);
      Emojidex::Data::Collection ending(std::string code_ew, Emojidex::Service::QueryOpts *conditions = NULL);
      Emojidex::Data::Collection tags(const std::vector<std::string> &tags, Emojidex::Service::QueryOpts *conditions = NULL);
      Emojidex::Data::Collection advanced(std::string code_cont, const std::vector<std::string> &categories,
          const std::vector<std::string> &tags, Emojidex::Service::QueryOpts *conditions = NULL);

      // Attempts to directly obtain emoji data by code
      // Returns a Data::Emoji object filled with the emoji info on success (the emoji is registered)
      // Returns an empty emoji object with only the code field filled on failure (the emoji is not registered)
      Emojidex::Data::Emoji find(std::string code, bool detailed = true);
    };
  }
}

// Rename template classes.
#ifndef TEMPLATE_STRING_VECTOR
#define TEMPLATE_STRING_VECTOR
%template(StringVector) std::vector<std::string>;
#endif
