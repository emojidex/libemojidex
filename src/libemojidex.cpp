#include "./libemojidex.h"
#include <regex>

std::string Emojidex::escapeCode(std::string code)
{
	code = std::regex_replace(code, std::regex(" "), "_");
	return code;
}

std::string Emojidex::unescapeCode(std::string code)
{
	code = std::regex_replace(code, std::regex("_"), " ");
	return code;
}

std::string Emojidex::encapsulateCode(std::string code)
{
	code = std::regex_replace(code, std::regex(":"), "");
	code.insert(code.begin(), Emojidex::encapsulator);
	code.insert(code.end(), Emojidex::encapsulator);
	return code;
}

std::string Emojidex::unencapsulateCode(std::string code)
{
	code = std::regex_replace(code, std::regex(":"), "");
	return code;
}
