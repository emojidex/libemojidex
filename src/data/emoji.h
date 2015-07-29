#ifndef EMOJIDEX_DATA_EMOJI_H
#define EMOJIDEX_DATA_EMOJI_H

#include <string>
#include <vector>
using namespace std;

#include "./checksums.h"

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
			vector<std::string> tags;
			string base;
			vector<std::string> variants;
			string link;
			// detailed
			bool is_wide;
			bool copyright_lock;
			unsigned int times_used;
			unsigned int times_favorited;
			int score;
			string attribution;
			string user_id;
			Checksums checksums;
		};
	}
}

#endif /* EMOJIDEX_DATA_EMOJI_H */
