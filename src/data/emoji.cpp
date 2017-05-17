#include "emoji.h"

#include <msgpack.hpp>

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
	if (d.HasMember("copyright_lock"))
		this->copyright_lock = d["copyright_lock"].GetBool();

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

#define OBJ2TYPE(dest, src, key, msgpack_type, result_type) { if(src.count(key) != 0 && src[key].type == msgpack_type) dest = src[key].as<result_type>(); }
#define OBJ2STR(dest, src, key) OBJ2TYPE(dest, src, key, msgpack::type::STR, std::string)
#define OBJ2INT(dest, src, key) OBJ2TYPE(dest, src, key, msgpack::type::POSITIVE_INTEGER, int)
#define OBJ2DOUBLE(dest, src, key) OBJ2TYPE(dest, src, key, msgpack::type::FLOAT64, double)
#define OBJ2BOOLEAN(dest, src,key) OBJ2TYPE(dest, src, key, msgpack::type::BOOLEAN, bool)

void Emojidex::Data::Emoji::fillFromMsgPack(const msgpack::object& d)
{
	auto m = d.as<std::map<std::string, msgpack::object>>();

	OBJ2STR(this->code, m, "code");
	OBJ2STR(this->moji, m, "moji");
	OBJ2STR(this->unicode, m, "unicode");
	OBJ2STR(this->category, m, "category");
	OBJ2STR(this->base, m, "base");
	OBJ2STR(this->link, m, "link");
	OBJ2INT(this->score, m, "score");
	OBJ2DOUBLE(this->current_price, m, "current_price");
	OBJ2BOOLEAN(this->permalock, m, "permalock");
	OBJ2INT(this->times_changed, m, "times_changed");
	OBJ2INT(this->times_used, m, "times_used");
	OBJ2STR(this->user_id, m, "user_id");
	OBJ2INT(this->favorited, m, "favorited");
	OBJ2BOOLEAN(this->copyright_lock, m, "copyright_lock");

	const msgpack::object& tags = m["tags"];
	assert(tags.type == msgpack::type::ARRAY);
	for(unsigned int i = 0;  i < tags.via.array.size;  ++i)
		this->tags.push_back(tags.via.array.ptr[i].as<std::string>());

	const msgpack::object& variants = m["variants"];
	assert(variants.type == msgpack::type::ARRAY);
	for(unsigned int i = 0;  i < variants.via.array.size;  ++i)
		this->variants.push_back(variants.via.array.ptr[i].as<std::string>());

	if(m.count("checksums") != 0)
	{
		auto checksums = m["checksums"].as<std::map<std::string, msgpack::object>>();

		if(checksums.count("svg") != 0)
		{
			OBJ2STR(this->checksums.svg, checksums, "svg");
		}

		if(checksums.count("png") != 0)
		{
			auto png = checksums["png"].as<std::map<std::string, msgpack::object>>();
			for(auto& kv : png)
			{
				if(kv.second.type == msgpack::type::STR)
					this->checksums.png[kv.first] = kv.second.as<std::string>();
			}
		}
	}
}
