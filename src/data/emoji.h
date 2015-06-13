#ifndef EMOJIDEX_DATA_EMOJI_H
#define EMOJIDEX_DATA_EMOJI_H

#include <string>
#include <vector>

#include "./checksums.h"

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

#endif /* EMOJIDEX_DATA_EMOJI_H */
