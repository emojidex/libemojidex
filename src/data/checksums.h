#ifndef EMOJIDEX_DATA_CHECKSUMS_H
#define EMOJIDEX_DATA_CHECKSUMS_H

#include <string>
#include <unordered_map>

namespace Emojidex {
	namespace Data {
		class Checksums
		{
		public:
			std::string svg;
			std::unordered_map <std::string, std::string> png;

			std::string sum(std::string format_code, std::string size_code);
		};
	}
}


#endif /* EMOJIDEX_DATA_CHECKSUMS_H */
