#ifndef EMOJIDEX_DATA_MOJI_CODES_H
#define EMOJIDEX_DATA_MOJI_CODES_H

#include <string>
#include <vector>

#include <unordered_map>

namespace Emojidex {
	namespace Data {
		// Moji code container with 3 types of moji code indexes
		class MojiCodes
		{
		public:
			std::string locale = "";
			std::string moji_string;
			std::vector<std::string> moji_array;
			std::unordered_map<std::string, std::string> moji_index;
		};
	}
}

#endif /* EMOJIDEX_DATA_MOJI_CODES_H */
