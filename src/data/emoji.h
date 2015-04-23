#ifndef EMOJIDEX_DATA_EMOJI_H
#define EMOJIDEX_DATA_EMOJI_H

#include <string>
#include <vector>
#include <unordered_map>
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

#endif /* EMOJIDEX_DATA_EMOJI_H */
