%module "Emojidex::Data::Emoji"

%include "std_string.i"
%include "std_vector.i"
%include "data/checksums.i"

%{
#include "data/emoji.h"
%}

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
