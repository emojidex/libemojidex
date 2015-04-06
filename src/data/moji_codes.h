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
			string mojiString;
			vector<string> mojiArray;
			unordered_map<string, string> mojiIndex;
		};
	}
}

#endif /* EMOJIDEX_DATA_MOJI_CODES_H */
