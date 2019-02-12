#include "emoji.h"

#include <msgpack.hpp>

//#define MSGPACK_OBJ2TYPE(dest, src, key, msgpack_type, result_type) { if(src.count(key) != 0 && src[key].type == msgpack_type) dest = src[key].as<result_type>(); }
#define MSGPACK_OBJ2TYPE(dest, src, key, msgpack_type, result_type) { if(src.count(key) != 0) { const msgpack::object target = src.at(key); if(target.type == msgpack_type) dest = target.as<result_type>(); } }
#define MSGPACK_OBJ2STR(dest, src, key) MSGPACK_OBJ2TYPE(dest, src, key, msgpack::type::STR, std::string)
#define MSGPACK_OBJ2INT(dest, src, key) MSGPACK_OBJ2TYPE(dest, src, key, msgpack::type::POSITIVE_INTEGER, int)
#define MSGPACK_OBJ2DOUBLE(dest, src, key) MSGPACK_OBJ2TYPE(dest, src, key, msgpack::type::FLOAT64, double)
#define MSGPACK_OBJ2BOOLEAN(dest, src,key) MSGPACK_OBJ2TYPE(dest, src, key, msgpack::type::BOOLEAN, bool)

namespace
{
	void fillChecksumsFromJSON(Emojidex::Data::Checksums *dest, const rapidjson::Value& src)
	{
		if (src.HasMember("svg")) {
			const rapidjson::Value& svg = src["svg"];
			if(svg.IsString())	dest->svg = svg.GetString();
		}

		if (src.HasMember("png")) {
			const rapidjson::Value& png = src["png"];
			for(rapidjson::Value::ConstMemberIterator it = png.MemberBegin();  it != png.MemberEnd();  ++it)
				if(it->name.IsString() && it->value.IsString())
					dest->png[it->name.GetString()] = it->value.GetString();
		}
	}

	void fillCombinationFromJSON(std::vector<Emojidex::Data::Combination> *dest, const rapidjson::Value& src)
	{
		assert(src.IsArray());
		for (rapidjson::SizeType i = 0; i < src.Size(); i++)
		{
			Emojidex::Data::Combination combination;
			const rapidjson::Value& data = src[i];

			if (data.HasMember("base")) {
				const rapidjson::Value& base = data["base"];
				if(base.IsString())	combination.base = base.GetString();
			}

			if (data.HasMember("component_layer_order")) {
				const rapidjson::Value& component_layer_order = data["component_layer_order"];
				assert(component_layer_order.IsArray());
				for (rapidjson::SizeType j = 0; j < component_layer_order.Size(); j++)
				{
					const rapidjson::Value& value = component_layer_order[j];
					if(value.IsUint())
						combination.component_layer_order.push_back(value.GetUint());
				}
			}

			if (data.HasMember("components")) {
				const rapidjson::Value& components = data["components"];
				assert(components.IsArray());
				for (rapidjson::SizeType j = 0; j < components.Size(); j++)
				{
					const rapidjson::Value& components_array = components[j];
					assert(components_array.IsArray());
					std::vector<std::string> new_components_array;
					for (rapidjson::SizeType k = 0; k < components_array.Size(); k++)
					{
						const rapidjson::Value& value = components_array[k];
						if(value.IsString())
							new_components_array.push_back(value.GetString());
					}
					combination.components.push_back(new_components_array);
				}
			}

			if (data.HasMember("checksums")) {
				const rapidjson::Value& checksums = data["checksums"];
				assert(checksums.IsArray());
				for (rapidjson::SizeType j = 0; j < checksums.Size(); j++)
				{
					const rapidjson::Value& checksums_map = checksums[j];
					std::unordered_map<std::string, Emojidex::Data::Checksums> new_checksums_map;
					for(rapidjson::Value::ConstMemberIterator it = checksums_map.MemberBegin();  it != checksums_map.MemberEnd();  ++it)
					{
						if(it->name.IsString())
						{
							Emojidex::Data::Checksums new_checksums;
							fillChecksumsFromJSON(&new_checksums, it->value);
							new_checksums_map[it->name.GetString()] = new_checksums;
						}
					}
					combination.checksums.push_back(new_checksums_map);
				}
			}

			dest->push_back(combination);
		}
	}

	void fillChecksumsFromMsgPack(Emojidex::Data::Checksums *dest, const msgpack::object &src)
	{
		auto data = src.as<std::map<std::string, msgpack::object>>();

		if(data.count("svg") != 0)
		{
			MSGPACK_OBJ2STR(dest->svg, data, "svg");
		}

		if(data.count("png") != 0)
		{
			auto png = data.at("png").as<std::map<std::string, msgpack::object>>();
			for(auto& kv : png)
			{
				if(kv.second.type == msgpack::type::STR)
					dest->png[kv.first] = kv.second.as<std::string>();
			}
		}
	}

	void fillCombinationFromMsgPack(std::vector<Emojidex::Data::Combination> *dest, const msgpack::object& src)
	{
		assert(src.type == msgpack::type::ARRAY);

		for(unsigned int i = 0;  i < src.via.array.size;  ++i)
		{
			Emojidex::Data::Combination combination;
			auto data = src.via.array.ptr[i].as<std::map<std::string, msgpack::object>>();

			MSGPACK_OBJ2STR(combination.base, data, "base");

			if(data.count("component_layer_order") != 0)
			{
				const msgpack::object& component_layer_order = data["component_layer_order"];
				assert(component_layer_order.type == msgpack::type::ARRAY);
				for(unsigned int j = 0;  j < component_layer_order.via.array.size;  ++j)
					combination.component_layer_order.push_back(component_layer_order.via.array.ptr[j].as<unsigned int>());
			}

			if(data.count("components") != 0)
			{
				const msgpack::object& components = data["components"];
				assert(components.type == msgpack::type::ARRAY);
				for(unsigned int j = 0;  j < components.via.array.size;  ++j)
				{
					const msgpack::object& components_array = components.via.array.ptr[j];
					assert(components_array.type == msgpack::type::ARRAY);
					std::vector<std::string> new_components_array;
					for(unsigned int k = 0;  k < components_array.via.array.size;  ++k)
						new_components_array.push_back(components_array.via.array.ptr[k].as<std::string>());
					combination.components.push_back(new_components_array);
				}
			}

			if(data.count("checksums") != 0)
			{
				const msgpack::object& checksums = data["checksums"];
				assert(checksums.type == msgpack::type::ARRAY);
				for(unsigned int j = 0;  j < checksums.via.array.size;  ++j)
				{
					auto checksums_map = checksums.via.array.ptr[j].as<std::map<std::string, msgpack::object>>();
					std::unordered_map<std::string, Emojidex::Data::Checksums> new_checksums_map;
					for(auto& kv : checksums_map)
					{
						Emojidex::Data::Checksums new_checksums;
						fillChecksumsFromMsgPack(&new_checksums, kv.second);
						new_checksums_map[kv.first] = new_checksums;
					}
					combination.checksums.push_back(new_checksums_map);
				}
			}

			dest->push_back(combination);
		}
	}
}

Emojidex::Data::Emoji::Emoji()
{
	this->moji = this->code = this->unicode = this->category = this->base = \
		this-> link = this->attribution = this->user_id = "";
	this->is_wide = this->copyright_lock = this->permalock = false;
	this->times_used = this->score = 0;
	this->current_price = 0.0;
	this->primary = true;
	this->registered_at = this->link_expiration = this->lock_expiration = "";
	this->times_changed = 0;
	this->favorited = 0;
	this->created_at = "";
	this->r18 = false;
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
	if(d.HasMember("error"))
		return;

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
	if (d.HasMember("created_at") && d["created_at"].IsString())
		this->created_at = d["created_at"].GetString();
	if (d.HasMember("r18") && d["r18"].IsBool())
		this->r18 = d["r18"].GetBool();

	rapidjson::Value& tags = d["tags"];
	assert(tags.IsArray());
	for (rapidjson::SizeType tag_i = 0; tag_i < tags.Size(); tag_i++)
		this->tags.push_back(tags[tag_i].GetString());

	rapidjson::Value& variants = d["variants"];
	assert(variants.IsArray());
	for (rapidjson::SizeType variant_i = 0; variant_i < variants.Size(); variant_i++)
		this->variants.push_back(variants[variant_i].GetString());

	if (d.HasMember("checksums"))
		fillChecksumsFromJSON(&this->checksums, d["checksums"]);

	if(d.HasMember("customizations"))
		fillCombinationFromJSON(&this->customizations, d["customizations"]);

	if(d.HasMember("combinations"))
		fillCombinationFromJSON(&this->combinations, d["combinations"]);
}

void Emojidex::Data::Emoji::fillFromMsgPack(const msgpack::object& d)
{
	auto m = d.as<std::map<std::string, msgpack::object>>();

	MSGPACK_OBJ2STR(this->code, m, "code");
	MSGPACK_OBJ2STR(this->moji, m, "moji");
	MSGPACK_OBJ2STR(this->unicode, m, "unicode");
	MSGPACK_OBJ2STR(this->category, m, "category");
	MSGPACK_OBJ2STR(this->base, m, "base");
	MSGPACK_OBJ2STR(this->link, m, "link");
	MSGPACK_OBJ2INT(this->score, m, "score");
	MSGPACK_OBJ2DOUBLE(this->current_price, m, "current_price");
	MSGPACK_OBJ2BOOLEAN(this->permalock, m, "permalock");
	MSGPACK_OBJ2INT(this->times_changed, m, "times_changed");
	MSGPACK_OBJ2INT(this->times_used, m, "times_used");
	MSGPACK_OBJ2STR(this->user_id, m, "user_id");
	MSGPACK_OBJ2INT(this->favorited, m, "favorited");
	MSGPACK_OBJ2BOOLEAN(this->copyright_lock, m, "copyright_lock");
	MSGPACK_OBJ2STR(this->created_at, m, "created_at");
	MSGPACK_OBJ2BOOLEAN(this->r18, m, "r18");

	const msgpack::object& tags = m["tags"];
	assert(tags.type == msgpack::type::ARRAY);
	for(unsigned int i = 0;  i < tags.via.array.size;  ++i)
		this->tags.push_back(tags.via.array.ptr[i].as<std::string>());

	const msgpack::object& variants = m["variants"];
	assert(variants.type == msgpack::type::ARRAY);
	for(unsigned int i = 0;  i < variants.via.array.size;  ++i)
		this->variants.push_back(variants.via.array.ptr[i].as<std::string>());

	if(m.count("checksums") != 0)
		fillChecksumsFromMsgPack(&this->checksums, m["checksums"]);

	if(m.count("customizations") != 0)
		fillCombinationFromMsgPack(&this->customizations, m["customizations"]);

	if(m.count("combinations") != 0)
		fillCombinationFromMsgPack(&this->combinations, m["combinations"]);
}
