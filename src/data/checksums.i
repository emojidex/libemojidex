%module Emojidex_Data_Checksums

%include "std_string.i"
%include "std_unordered_map.i"

%{
include "data/checksums.h"
%}

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
