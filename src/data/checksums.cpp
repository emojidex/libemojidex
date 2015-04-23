#include "./checksums.h"

string Emojidex::Data::Checksums::sum(string format_code, string size_code)
{
	if (format_code.compare("svg") == 0)
		return this->svg;

	if (format_code.compare("png") == 0)
		return png[size_code];

	return "";
}
