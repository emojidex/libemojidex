#ifndef EMOJIDEX_DATA_EMOJI_H
#define EMOJIDEX_DATA_EMOJI_H

#include <string>
#include <vector>

#include "./checksums.h"
#include "rapidjson/document.h"

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
			unsigned int times_used;
			unsigned int times_favorited;
			int score;
			std::string attribution;
			std::string user_id;
			Emojidex::Data::Checksums checksums;

			Emoji();

			void fillFromJSONString(std::string json);
			void fillFromJSON(rapidjson::Value& d);
		};
	}
}

#endif /* EMOJIDEX_DATA_EMOJI_H */
