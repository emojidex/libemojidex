%module DataEmoji

%include "std_string.i"
%include "std_vector.i"

%{
#include "data/emoji.h"
%}

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
			vector<string> tags;
			string base;
			vector<string> variants;
			string link;
			// detailed
			bool is_wide;
			bool copyright_lock;
			int times_used;
			string attribution;
			string user_id;
			Checksums checksums;
		};
	}
}
