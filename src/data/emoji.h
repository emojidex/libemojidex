#ifndef EMOJIDEX_DATA_EMOJI_H
#define EMOJIDEX_DATA_EMOJI_H

#include <string>
#include <vector>
#include <msgpack.hpp>

#include "./checksums.h"
#include "./combination.h"
#include "rapidjson/document.h"

namespace Emojidex {
	namespace Data {
		//! emoji data container
		class Emoji
		{
		public:
			//! The moji [character] or compound
			/*!
			 * Standard emoji only. This contians the actual caracter or set 
			 * of chracters. For example it could be "💩"
			 */
			std::string moji;
			//! The name code/short code of the emoji
			std::string code;
			//! The unicode ID of the emoji
			std::string unicode;
			//! The category this emoji belongs in
			std::string category;
			//! The tags associated with this emoji
			std::vector<std::string> tags;
			//! The base emoji (what variants are based off of)
			/*!
			 * In the case that this emoji is its own base, this value will be the 
			 * same as the code attribute.
			 */
			std::string base;
			//! The variants/variations of this emoji
			std::vector<std::string> variants;
			//! The link URL associated with this emoji, if any.
			std::string link;
			// detailed
			//! Identifies if the image associated with this emoji is wide
			bool is_wide;
			//! Identifies if copyright protection (no commercial use) has been applied
			bool copyright_lock;
			//! The number of times this emoji has been used
			unsigned int times_used;
			//! The score (weighted popularity, times used, and other factors)
			int score;
			//! The owner/author of the images and/or information of this emoji
			std::string attribution;
			//! The ID of the user who registered/controlls this emoji
			std::string user_id;
			//! The price of the control rights to this emoji
			double current_price;
			//! Identifies if this is the primary record for an emoji (rarely important)
			bool primary;
			//! Identifies if this emoji has been permanantly locked to an account
			bool permalock;
			//! Date the emoji was registered
			std::string registered_at;
			//! Date the link associated with this emoji expires (if there is a link)
			std::string link_expiration;
			//! Date the lock on this emoji expires (if there is a lock)
			std::string lock_expiration;
			//! Number of times this emoji has been edited/the image has changed
			unsigned int times_changed;
			//! Number of users who have added this emoji to their favorites
			unsigned int favorited;
			//! Date the emoji was created
			std::string created_at;
			//! specifies if the emoji contains adult/vulgar content (requires account with R-18 enabled)
			bool r18;
			//! specifies overlays to customize the emoji
			std::vector<Emojidex::Data::Combination> customizations;
			//! specifies combinations this emoji can be used in
			std::vector<Emojidex::Data::Combination> combinations;

			//! List of checksums for images. Use this to check if your images are up to date
			Emojidex::Data::Checksums checksums;

			Emoji();

			//! Fill the emoji information from a raw JSON string
			void fillFromJSONString(std::string json);
			//! Fill the emoji information from a RapidJSON value
			void fillFromJSON(rapidjson::Value& d);
			//! Fill the emoji information from a msgpack object
			void fillFromMsgPack(const msgpack::object& d);
		};
	}
}

#endif /* EMOJIDEX_DATA_EMOJI_H */
