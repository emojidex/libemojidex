#ifndef EMOJIDEX_DATA_MOJI_CODES_H
#define EMOJIDEX_DATA_MOJI_CODES_H

#include <string>
#include <vector>

#include <unordered_map>

namespace Emojidex {
	namespace Data {
		//! Moji [character] code container with 3 types of moji code indexes
		class MojiCodes
		{
		public:
			//! The locale of the codes in this instance
			std::string locale = "";
			//! A large string of just emoji, sorted compount longest first
			/*!
			 * Use this for regex to detect emoji within text or to validate 
			 * emoji / determine if a charater is an emoji.
			 */
			std::string moji_string;
			//! An array with each item containing a single emoji, compount longest first
			std::vector<std::string> moji_array;
			//! A hash/map of emoji and their short codes in the given locale
			std::unordered_map<std::string, std::string> moji_index;
		};
	}
}

#endif /* EMOJIDEX_DATA_MOJI_CODES_H */
