#include "emoji.h"

Emojidex::Data::Emoji::Emoji()
{
	this->moji = this->code = this->unicode = this->category = this->base = \
		this-> link = this->attribution = this->user_id = "";
	this->is_wide = this->copyright_lock = this->permalock = false;
	this->times_used = this->times_favorited = this->score = 0;
	this->current_price = 0.0;
	this->primary = true;
	this->registered_at = this->link_expiration = this->lock_expiration = "";
	this->times_changed = 0;
	this->favorited = 0;
}

void Emojidex::Data::Emoji::fillFromJSONString(std::string json)
{
	rapidjson::Document d;
	d.Parse(json.c_str());

	if (d.HasParseError())
		return;

	this->fillFromJSON(d);
}

void Emojidex::Data::Emoji::fillFromJSON(rapidjson::Value& d)
{
	this->code = d["code"].GetString();
	if (d["moji"].IsString()) { this->moji = d["moji"].GetString(); }
	if (d["unicode"].IsString()) { this->unicode = d["unicode"].GetString(); }
	if (d["category"].IsString()) { this->category = d["category"].GetString(); }
	if (d["base"].IsString()) { this->base = d["base"].GetString(); }
	if (d["link"].IsString()) { this->link = d["link"].GetString(); }
	if (d["score"].IsUint()) { this->score = d["score"].GetUint(); }
	if (d.HasMember("current_price") && d["current_price"].IsDouble())
		this->current_price = d["current_price"].GetDouble();
	if (d.HasMember("permalock") && d["permalock"].IsBool())
		this->permalock = d["permalock"].GetBool();
	if (d.HasMember("times_changed") && d["times_changed"].IsUint())
		this->times_changed = d["times_changed"].GetUint();
	if (d.HasMember("times_used") && d["times_used"].IsUint())
		this->times_used = d["times_used"].GetUint();
	if (d.HasMember("user_id") && d["user_id"].IsString())
		this->user_id = d["user_id"].GetString();
	if (d.HasMember("favorited") && d["favorited"].IsUint())
		this->favorited = d["favorited"].GetUint();

	rapidjson::Value& tags = d["tags"];
	assert(tags.IsArray());
	for (rapidjson::SizeType tag_i = 0; tag_i < tags.Size(); tag_i++)
		this->tags.push_back(tags[tag_i].GetString());

	rapidjson::Value& variants = d["variants"];
	assert(variants.IsArray());
	for (rapidjson::SizeType variant_i = 0; variant_i < variants.Size(); variant_i++)
		this->variants.push_back(variants[variant_i].GetString());

	if (d.HasMember("checksums"))
	{
		const rapidjson::Value& checksums = d["checksums"];
		
		if (checksums.HasMember("svg")) {
			const rapidjson::Value& svg = checksums["svg"];
			if(svg.IsString())	this->checksums.svg = svg.GetString();
		}

		if (checksums.HasMember("png")) {
			const rapidjson::Value& png = checksums["png"];
			for(rapidjson::Value::ConstMemberIterator it = png.MemberBegin();  it != png.MemberEnd();  ++it)
				if(it->value.IsString())	this->checksums.png[it->name.GetString()] = it->value.GetString();
		}
	}
}
