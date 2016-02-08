#include "search.h"
#include "transactor.h"

#define TF(bv) ((bv)?"true":"false")

using namespace std;

namespace
{
  void unencapsulate(std::string *code)
  {
    size_t pos;
    while( (pos = code->find(':')) != std::string::npos )
      code->erase(pos, 1);
  }

  void url_encode(std::string *code)
  {
    // todo
  }
}

Emojidex::Service::Search::Search()
{
	this->current_page = 0;
}

Emojidex::Data::Collection Emojidex::Service::Search::term(std::string code_cont, Emojidex::Service::QueryOpts conditions)
{
	Emojidex::Data::Collection results;

	return results;
}

Emojidex::Data::Emoji Emojidex::Service::Search::find(std::string code, bool detailed)
{
  unencapsulate(&code);
  url_encode(&code);
  code = "emoji/" + code;

  // Get emoji data.
  Emojidex::Service::Transactor transactor;
  std::string json_string = transactor.GET(code, {{"detailed", TF(detailed)}});
  
printf("%s\n%s\n", code.c_str(), json_string.c_str());

  // Create emoji object.
  Emojidex::Data::Emoji result;
  result.fillFromJSONString(json_string);

  return result;
}
