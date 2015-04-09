#ifndef EMOJIDEX_DATA_MOJI_CODES_H
#define EMOJIDEX_DATA_MOJI_CODES_H

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

namespace Emojidex {
	namespace Data {
		// Moji code container with 3 types of moji code indexes
		class MojiCodes
		{
		public:
			string locale = "";
			string moji_string;
			vector<string> moji_array;
			unordered_map<string, string> moji_index;
		};
	}
}

#endif /* EMOJIDEX_DATA_MOJI_CODES_H */
