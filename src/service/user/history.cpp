#include "history.h"

Emojidex::Service::HistoryItem::HistoryItem(std::string emoji_code, unsigned int times_used, std::string last_used)
{
	this->emoji_code = emoji_code;
	this->times_used = times_used;
	this->last_used = last_used;
}
