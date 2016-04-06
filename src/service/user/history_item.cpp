#include "history_item.h"

Emojidex::Service::HistoryItem::HistoryItem()
{
  this->emoji_code = "";
  this->times_used = 0;
  this->last_used = "";
}

Emojidex::Service::HistoryItem::HistoryItem(std::string emoji_code, unsigned int times_used, std::string last_used)
{
	this->emoji_code = emoji_code;
	this->times_used = times_used;
	this->last_used = last_used;
	boost::posix_time::time_input_facet *tif = new boost::posix_time::time_input_facet("%Y-%m-%dT%H:%M:%S%f%Q");
	std::stringstream ss;
	ss.imbue(std::locale(std::locale(), tif));
	ss << last_used;
	ss >> this->last_used_posix;
}
