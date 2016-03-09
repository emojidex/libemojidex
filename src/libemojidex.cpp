#include "./libemojidex.h"
#include <boost/algorithm/string.hpp>
#include <regex>

std::string Emojidex::escapeCode(std::string code)
{
	code = std::regex_replace(code, std::regex(" "), "_");
	//boost::replace_all(code, "(", "\\(");
	//boost::replace_all(code, ")", "\\)");
	//code.replace(")", "\\)");
	//code = std::regex_replace(code, std::regex("\("), "\\(");
	//code = std::regex_replace(code, std::regex("\)"), "\\)");
	return code;
}

std::string Emojidex::unescapeCode(std::string code)
{
	code = std::regex_replace(code, std::regex("_"), " ");
	//boost::replace_all(code, "\\", "");// = std::string::replace_all(code, std::regex("\\"), "");
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



namespace
{
	std::string CACertPath = "";
}

void Emojidex::setCACertPath(const std::string &path)
{
	CACertPath = path;
}

const std::string& Emojidex::getCACertPath(void)
{
	return CACertPath;
}
