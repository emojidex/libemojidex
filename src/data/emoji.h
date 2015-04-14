#ifndef EMOJIDEX_DATA_EMOJI_H
#define EMOJIDEX_DATA_EMOJI_H

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

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

#endif /* EMOJIDEX_DATA_EMOJI_H */
