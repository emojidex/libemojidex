#ifndef EMOJIDEX_DATA_CHECKSUMS_H
#define EMOJIDEX_DATA_CHECKSUMS_H

#include <string>
#include <unordered_map>
using namespace std;

namespace Emojidex {
	namespace Data {
		class Checksums
		{
		public:
			string svg;
			unordered_map <string, string> png;

			string sum(string format_code, string size_code);
		};
	}
}


#endif /* EMOJIDEX_DATA_CHECKSUMS_H */
