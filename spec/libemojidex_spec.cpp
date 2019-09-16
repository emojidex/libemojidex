#include <libemojidex.h>
#include <client.h>
#include <service/settings.h>
#include <service/transactor.h>

#include <stdlib.h>

using namespace std;

#define BOOST_TEST_DYN_LINK 
#define BOOST_TEST_MODULE emojidex_test
#include <boost/test/unit_test.hpp>


///////////////////////////////////////////////////////////////////////////////
// libemojidex Utility test
///////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(libemojidex_utility_suite)
	BOOST_AUTO_TEST_CASE(code_utilities) {
		BOOST_TEST_MESSAGE("Checking code unescape:");
		std::string escaped_code = Emojidex::escapeCode(":test code:");
		BOOST_TEST_MESSAGE("Escaping ':test code:' results in: " << escaped_code);
		BOOST_CHECK_EQUAL(escaped_code.compare(":test_code:"), 0);

		BOOST_TEST_MESSAGE("Checking code escape:");
		std::string unescaped_code = Emojidex::unescapeCode("test_code");
		BOOST_TEST_MESSAGE("Unescaping 'test_code' results in: " << unescaped_code);
		BOOST_CHECK_EQUAL(unescaped_code.compare("test code"), 0);

		BOOST_TEST_MESSAGE("Checking code encapsulate:");
		std::string encap_code = Emojidex::encapsulateCode("test code");
		BOOST_TEST_MESSAGE("Encapsulating 'test code' results in: " << encap_code);
		BOOST_CHECK_EQUAL(encap_code.compare(":test code:"), 0);
		encap_code = Emojidex::encapsulateCode(":test code:");
		BOOST_TEST_MESSAGE("Encapsulating ':test code:' results in: " << encap_code);
		BOOST_CHECK_EQUAL(encap_code.compare(":test code:"), 0);

		BOOST_TEST_MESSAGE("Checking code unencapsulate:");
		std::string unencap_code = Emojidex::unencapsulateCode(":test code:");
		BOOST_TEST_MESSAGE("Unencapsulating ':test code:' results in: " << unencap_code);
		BOOST_CHECK_EQUAL(unencap_code.compare("test code"), 0);
	}
BOOST_AUTO_TEST_SUITE_END()

///////////////////////////////////////////////////////////////////////////////
// Emoji data container test
///////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(data_emoji_suite)
	BOOST_AUTO_TEST_CASE(emoji_data) {
		BOOST_TEST_MESSAGE("Checking emoji data fill from JSON string:");
		Emojidex::Data::Emoji em;
		em.fillFromJSONString("{\"code\":\"zipper mouth face\",\"moji\":\"🤐\","
				"\"unicode\":\"1f910\",\"category\":\"faces\",\"tags\":[\"silence\"],\"link\":null,"
				"\"base\":\"zipper_mouth_face\",\"variants\":[\"zipper_mouth_face(wh)\","
				"\"zipper_mouth_face(p)\",\"zipper_mouth_face(ye)\",\"zipper_mouth_face(br)\","
				"\"zipper_mouth_face(bk)\",\"zipper_mouth_face\",\"zipper_mouth_face(smiley)\"],"
				"\"score\":10}");
		BOOST_CHECK_EQUAL(em.code.compare("zipper mouth face"), 0);
		BOOST_CHECK_EQUAL(em.moji.compare("🤐"), 0);
		BOOST_CHECK_EQUAL(em.unicode.compare("1f910"), 0);
		BOOST_CHECK_EQUAL(em.category.compare("faces"), 0);
		BOOST_CHECK_EQUAL(em.tags.size(), 1);
		BOOST_CHECK_EQUAL(em.tags[0].compare("silence"), 0);
		BOOST_CHECK_EQUAL(em.link.compare(""), 0);
		BOOST_CHECK_EQUAL(em.base.compare("zipper_mouth_face"), 0);
		BOOST_CHECK_EQUAL(em.variants.size(), 7);
		BOOST_CHECK_EQUAL(em.variants[0].compare("zipper_mouth_face(wh)"), 0);
		BOOST_CHECK_EQUAL(em.score, 10);
	}

	BOOST_AUTO_TEST_CASE(emoji_data_detailed) {
		BOOST_TEST_MESSAGE("Checking detailed emoji data fill from JSON string:");
		Emojidex::Data::Emoji em;
		em.fillFromJSONString("{\"code\":\"zipper mouth face\",\"moji\":\"🤐\","
				"\"unicode\":\"1f910\",\"category\":\"faces\",\"tags\":[\"silence\"],\"link\":null,"
				"\"base\":\"zipper_mouth_face\",\"variants\":[\"zipper_mouth_face(wh)\","
				"\"zipper_mouth_face(p)\",\"zipper_mouth_face(ye)\",\"zipper_mouth_face(br)\","
				"\"zipper_mouth_face(bk)\",\"zipper_mouth_face\",\"zipper_mouth_face(smiley)\"],"
				"\"score\":10,\"current_price\":1.0,\"primary\":true,\"registered_at\":null,"
				"\"permalock\":true,\"copyright_lock\":false,\"link_expiration\":null,"
				"\"lock_expiration\":null,\"times_changed\":2,\"is_wide\":false,\"times_used\":8,"
				"\"attribution\":null,\"user_id\":\"emoji\",\"checksums\":{"
				"\"svg\":\"64f320f87517fc31fbf7f798a77d980b\",\"png\":{"
				"\"ldpi\":\"cf5dca7b0c71ee482fba3faa5f802eef\",\"mdpi\":"
				"\"6ddc276b2850459f2a018d1dec5f1632\",\"hdpi\":"
				"\"e70ffdce3d9bb87f2247283b53353aa8\",\"xhdpi\":"
				"\"18bbc85e597838a26b7e40a7361bfcf1\",\"xxhdpi\":"
				"\"6bb35d9169c4f1a98293591222df0d9e\",\"xxxhdpi\":"
				"\"f16e94d9a4d6e58f6f7f6a6f4c362bf4\",\"px8\":"
				"\"549e037f61ffc3091a2d774abe01f94e\",\"px16\":"
				"\"69b7725278aaf136f8908bf51c412874\",\"px32\":"
				"\"8ba5e03812aa5f0df249ab0162816216\",\"px64\":"
				"\"bfcfe6cbcc71525b4651541b62ba0db4\",\"px128\":"
				"\"cc1e8638ebc062dbcfb3521d840901c7\",\"px256\":"
				"\"eea71418b65007ebb76b7fad531f0211\",\"px512\":"
				"\"c3a4d09276b2f9a4c45d56685651e026\",\"hanko\":"
				"\"7bd6808ea4edd2acd0636b73a99d4a01\",\"seal\":"
				"\"e1bfb5385d58f65c23cb7c2e6045ae1e\"}},\"favorited\":5}");
		BOOST_CHECK_EQUAL(em.code.compare("zipper mouth face"), 0);
		BOOST_CHECK_EQUAL(em.moji.compare("🤐"), 0);
		BOOST_CHECK_EQUAL(em.unicode.compare("1f910"), 0);
		BOOST_CHECK_EQUAL(em.category.compare("faces"), 0);
		BOOST_CHECK_EQUAL(em.tags.size(), 1);
		BOOST_CHECK_EQUAL(em.tags[0].compare("silence"), 0);
		BOOST_CHECK_EQUAL(em.link.compare(""), 0);
		BOOST_CHECK_EQUAL(em.base.compare("zipper_mouth_face"), 0);
		BOOST_CHECK_EQUAL(em.variants.size(), 7);
		BOOST_CHECK_EQUAL(em.variants[0].compare("zipper_mouth_face(wh)"), 0);
		BOOST_CHECK_EQUAL(em.score, 10);
		BOOST_CHECK_EQUAL(em.current_price, 1.0);
		BOOST_CHECK_EQUAL(em.primary, true);
		BOOST_CHECK_EQUAL(em.registered_at.compare(""), 0);
		BOOST_CHECK_EQUAL(em.permalock, true);
		BOOST_CHECK_EQUAL(em.copyright_lock, false);
		BOOST_CHECK_EQUAL(em.link_expiration.compare(""), 0);
		BOOST_CHECK_EQUAL(em.lock_expiration.compare(""), 0);
		BOOST_CHECK_EQUAL(em.times_changed, 2);
		BOOST_CHECK_EQUAL(em.is_wide, false);
		BOOST_CHECK_EQUAL(em.times_used, 8);
		BOOST_CHECK_EQUAL(em.attribution.compare(""), 0);
		BOOST_CHECK_EQUAL(em.user_id.compare("emoji"), 0);
		BOOST_CHECK_EQUAL(em.checksums.svg.compare("64f320f87517fc31fbf7f798a77d980b"), 0);
		BOOST_CHECK_EQUAL(em.checksums.png["hdpi"].compare("e70ffdce3d9bb87f2247283b53353aa8"), 0);
		BOOST_CHECK_EQUAL(em.favorited, 5);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(data_container_suite)
	BOOST_AUTO_TEST_CASE(basic_container_usage) {
		Emojidex::Data::Collection col;
		BOOST_CHECK(col.emoji.size() == 0);
		Emojidex::Data::Emoji em = Emojidex::Data::Emoji();
		em.code = "a";
		em.category = "people";
		col.add(em);
		BOOST_CHECK(col.emoji.size() == 1);
		em.code = "b";
		em.category = "faces";
		col.add(em);
		BOOST_CHECK(col.emoji.size() == 2);
		BOOST_CHECK(col.emoji["b"].category.compare("faces") == 0);
		//Now re-add last emoji, code is the same so should update
		col.add(em);
		BOOST_CHECK(col.emoji.size() == 2);
		//Test emoji is being updated
		em.category = "people";
		col.add(em);
		BOOST_CHECK(col.emoji.size() == 2);
		BOOST_CHECK(col.emoji["b"].category.compare("people") == 0);
		//See if we can find an emoji by code
		//TODO
		//See if we get a blank emoji when that code isn't found in our map
		//TODO
		//Make sure the blank emoji isn't actually added to the map (default map behavior)
		//TODO
	}
BOOST_AUTO_TEST_SUITE_END()

///////////////////////////////////////////////////////////////////////////////
// Settings tests
///////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(service_settings_suite)
	// Check that defaults are accurate
	BOOST_AUTO_TEST_CASE(settings_defaults) {
		BOOST_TEST_MESSAGE("Checking defaults:");
		BOOST_CHECK_EQUAL(Emojidex::Service::Settings::api_host, "www.emojidex.com");
		BOOST_CHECK_EQUAL(Emojidex::Service::Settings::api_prefix, "/api/v1/");
		BOOST_CHECK_EQUAL(Emojidex::Service::Settings::api_protocol, "https");
		BOOST_CHECK_EQUAL(Emojidex::Service::Settings::cdn_host, "cdn.emojidex.com");
		BOOST_CHECK_EQUAL(Emojidex::Service::Settings::cdn_prefix, "/emoji/");
		BOOST_CHECK_EQUAL(Emojidex::Service::Settings::cdn_protocol, "http");
		BOOST_CHECK_EQUAL(Emojidex::Service::Settings::closed_net, false);
	}
BOOST_AUTO_TEST_SUITE_END()

///////////////////////////////////////////////////////////////////////////////
// Transactor tests
///////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(service_transactor_suite)
	Emojidex::Service::Transactor transactor;

	BOOST_AUTO_TEST_CASE(transactor_get_no_query) {
		BOOST_TEST_MESSAGE("Transactor GET");
		BOOST_CHECK_NE(transactor.GET("emoji").compare(""), 0);
	}

	BOOST_AUTO_TEST_CASE(transactor_get_w_query_map) {
		BOOST_TEST_MESSAGE("Transactor GET with a query map");
		std::unordered_map<string, string> q;
		q["detailed"] = "true";
		q["limit"] = "10";
		q["page"] = "2";
		BOOST_CHECK_NE(transactor.GET("emoji", q).compare(""), 0);
	}

	BOOST_AUTO_TEST_CASE(transactor_get_hash_query) {
		BOOST_TEST_MESSAGE("Transactor GET with an instance query map");
		BOOST_CHECK_NE(transactor.GET("emoji", {{"detailed", "true"}, {"page", "3"}}).compare(""), 0);
	}

	BOOST_AUTO_TEST_CASE(transactor_get_static_point) {
		BOOST_TEST_MESSAGE("Transactor GET against a static endpoint");
		BOOST_CHECK_NE(transactor.GET("moji_codes").compare(""), 0);
		BOOST_CHECK_NE(transactor.GET("moji_codes", {{"locale", "ja"}}).compare(""), 0);
	}

	BOOST_AUTO_TEST_CASE(transactor_post_favorites) {
		BOOST_TEST_MESSAGE("Transactor POST");
		const std::string result = transactor.POST("users/favorites", {
			{"auth_token", "1798909355d57c9a93e3b82d275594e7c7c000db05021138"},
			{"emoji_code", "zebra"}
		});
		const msgpack::object_handle oh = msgpack::unpack(result.data(), result.size());
		const msgpack::object root = oh.get();
		const auto m = root.as<std::map<std::string, std::string>>();
		const std::string status = m.at("status");
		BOOST_CHECK_NE(result.compare(""), 0);
		BOOST_CHECK_NE(status.compare("wrong authentication token"), 0);
		BOOST_CHECK_NE(status.compare("emoji code is wrong"), 0);
	}

	BOOST_AUTO_TEST_CASE(transactor_delete_favorites) {
		BOOST_TEST_MESSAGE("Transactor DELETE");
		const std::string result = transactor.DELETE("users/favorites", {
			{"auth_token", "1798909355d57c9a93e3b82d275594e7c7c000db05021138"},
			{"emoji_code", "zebra"}
		});
		const msgpack::object_handle oh = msgpack::unpack(result.data(), result.size());
		const msgpack::object root = oh.get();
		const auto m = root.as<std::map<std::string, std::string>>();
		const std::string status = m.at("status");
		BOOST_CHECK_NE(result.compare(""), 0);
		BOOST_CHECK_NE(status.compare("wrong authentication token"), 0);
		BOOST_CHECK_NE(status.compare("emoji code is wrong"), 0);
	}
BOOST_AUTO_TEST_SUITE_END()

///////////////////////////////////////////////////////////////////////////////
// Query Options tests
///////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(query_opts_suite)
	Emojidex::Service::QueryOpts conditions;

	BOOST_AUTO_TEST_CASE(query_opts_building) {
		BOOST_CHECK(conditions.getPage() == 1);
		BOOST_CHECK(conditions.page(2).getPage() == 2);
		BOOST_CHECK(conditions.detailed(false).getDetailed() == false);
		conditions.ext("code=abc");
		BOOST_CHECK(conditions.getExt().compare("&code=abc") == 0);
		conditions.ext("code=abc");
		BOOST_CHECK(conditions.getExt().compare("&code=abc&code=abc") == 0);
	}
BOOST_AUTO_TEST_SUITE_END()

///////////////////////////////////////////////////////////////////////////////
// Collection tests
///////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(collection_suite)

	BOOST_AUTO_TEST_CASE(collect_params_from_query_opts) {
		Emojidex::Data::Collection collect;
		collect.opts.auth_token("a1234").username("Z").tag("testing").tag("テスト").page(5).limit(33).detailed(true);
		collect.opts.category("faces").category("nature");
		BOOST_CHECK(collect.opts.getUsername().compare("Z") == 0);
		BOOST_CHECK(collect.opts.getAuthToken().compare("a1234") == 0);
		BOOST_CHECK(collect.opts.getTags().size() == 2);
		BOOST_CHECK(collect.opts.getTags()[0].compare("testing") == 0);
		BOOST_CHECK(collect.opts.getTags()[1].compare("テスト") == 0);
		BOOST_CHECK(collect.opts.getCategories()[1].compare("nature") == 0);
		BOOST_CHECK(collect.opts.getPage() == 5);
		BOOST_CHECK(collect.opts.getLimit() == 33);
		BOOST_CHECK(collect.opts.getDetailed() == true);
		collect.opts.detailed(false).tag("third");
		BOOST_CHECK(collect.opts.getDetailed() == false);
		BOOST_CHECK(collect.opts.getTags().size() == 3);
	}
BOOST_AUTO_TEST_SUITE_END()

///////////////////////////////////////////////////////////////////////////////
// Index tests
///////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(service_indexes_suite)
	Emojidex::Service::Indexes idx;

	BOOST_AUTO_TEST_CASE(moji_codes_seed) {
		BOOST_TEST_MESSAGE("Index mojiCodes");
		BOOST_CHECK(idx.mojiCodes().locale.compare("en") == 0);
		BOOST_CHECK_GT(idx.mojiCodes().moji_array.size(), 0);
		BOOST_CHECK_GT(idx.mojiCodes().moji_index.size(), 0);
		BOOST_CHECK(idx.mojiCodes().moji_index["🍕"].compare("pizza") == 0);
		BOOST_CHECK(idx.mojiCodes("ja").locale.compare("ja") == 0);
	}

	BOOST_AUTO_TEST_CASE(moji_codes_seed_ja) {
		BOOST_TEST_MESSAGE("Index mojiCodes (ja)");
		Emojidex::Data::MojiCodes mc = idx.mojiCodes("ja");
		BOOST_CHECK(mc.locale.compare("ja") == 0);
		BOOST_CHECK_GT(mc.moji_array.size(), 0);
		BOOST_CHECK_GT(mc.moji_index.size(), 0);
		BOOST_CHECK(mc.moji_index["🌢"].compare("雫") == 0);
	}

	BOOST_AUTO_TEST_CASE(utf_emoji_seed) {
		BOOST_TEST_MESSAGE("Index utfEmoji");
		Emojidex::Data::Collection utf = idx.utfEmoji("ja");
		BOOST_CHECK(utf.opts.getLocale().compare("ja") == 0);
		BOOST_CHECK(utf.opts.getPage() == 1);
		BOOST_CHECK_GT(utf.emoji.size(), 0);
		BOOST_CHECK(utf.emoji["雫"].moji.compare("🌢") == 0);
		//Make sure we only loaded one language
		BOOST_CHECK(utf.emoji["droplet"].moji.compare("") == 0);
	}

	BOOST_AUTO_TEST_CASE(extended_emoji_seed) {
		BOOST_TEST_MESSAGE("Index extendedEmoji");
		Emojidex::Data::Collection ext = idx.extendedEmoji();
		BOOST_CHECK(ext.opts.getLocale().compare("en") == 0);
		BOOST_CHECK(ext.opts.getPage() == 1);
		BOOST_CHECK_GT(ext.emoji.size(), 0);
		BOOST_CHECK(ext.emoji["ninja"].category.compare("people") == 0);
		BOOST_CHECK(ext.emoji["smiling face"].category.compare("faces") == 0);
	}

	BOOST_AUTO_TEST_CASE(emoji_index) {
		BOOST_TEST_MESSAGE("Index emoji");
		Emojidex::Data::Collection emoji = idx.emoji();
		int sz = emoji.emoji.size();
		BOOST_CHECK(emoji.opts.getPage() == 1);
		BOOST_CHECK_GT(sz, 0);
		BOOST_CHECK_GT(emoji.total_count, sz);
		BOOST_CHECK_GT(emoji.more().emoji.size(), 0);
		BOOST_CHECK(emoji.opts.getPage() == 2);
		BOOST_CHECK_GT(emoji.emoji.size(), sz);
	}

	BOOST_AUTO_TEST_CASE(emoji_index_detailed) {
		BOOST_TEST_MESSAGE("Index emoji (detailed)");
		Emojidex::Data::Collection emoji = idx.emoji(1, 20, true);
		int sz = emoji.emoji.size();
		BOOST_CHECK(emoji.opts.getPage() == 1);
		BOOST_CHECK(sz == 20);
		BOOST_CHECK_GT(emoji.more().emoji.size(), 0);
		BOOST_CHECK(emoji.opts.getPage() == 2);
		BOOST_CHECK_EQUAL(emoji.emoji.size(), 40);
		BOOST_CHECK(emoji.emoji.begin()->second.checksums.svg.compare("") != 0);
		BOOST_CHECK(emoji.emoji.begin()->second.checksums.png["xhdpi"].compare("") != 0);
	}


	BOOST_AUTO_TEST_CASE(newest_index) {
		BOOST_TEST_MESSAGE("Index newest");
		if (std::getenv("EMOJIDEX_AUTH_TOKEN") != NULL) {
			std::string auth_token = std::string(getenv("EMOJIDEX_AUTH_TOKEN"));

			Emojidex::Data::Collection newest = idx.newest(auth_token);
			int sz = newest.emoji.size();
			BOOST_CHECK(newest.opts.getPage() == 1);
			BOOST_CHECK_GT(sz, 0);
			BOOST_CHECK_GT(newest.more().emoji.size(), 0);
			BOOST_CHECK(newest.opts.getPage() == 2);
			BOOST_CHECK_GT(newest.emoji.size(), sz);
		}
		//TODO make sure no auth token returns empty
	}

	BOOST_AUTO_TEST_CASE(popular_index) {
		BOOST_TEST_MESSAGE("Index popular");
		if (std::getenv("EMOJIDEX_AUTH_TOKEN") != NULL) {
			std::string auth_token = std::string(getenv("EMOJIDEX_AUTH_TOKEN"));
			
			Emojidex::Data::Collection popular = idx.popular(auth_token);
			int sz = popular.emoji.size();
			BOOST_CHECK(popular.opts.getPage() == 1);
			BOOST_CHECK_GT(sz, 0);
			BOOST_CHECK_GT(popular.more().emoji.size(), 0);
			BOOST_CHECK(popular.opts.getPage() == 2);
			BOOST_CHECK_GT(popular.emoji.size(), sz);
		}
		//TODO make sure no auth token returns empty
	}

	BOOST_AUTO_TEST_CASE(user_emoji_index) {
		Emojidex::Data::Collection user_emoji = idx.userEmoji("Zero");
		BOOST_CHECK_GT(user_emoji.emoji.size(), 0);
	}

BOOST_AUTO_TEST_SUITE_END()

///////////////////////////////////////////////////////////////////////////////
// Search tests
///////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(service_search_suite)
	Emojidex::Service::Search search;

	BOOST_AUTO_TEST_CASE(search_find) {
		Emojidex::Data::Emoji em = search.find("幻", false);
		BOOST_CHECK(em.checksums.sum("png", "px32").compare("743b2af6d489390821f0e56a5d357b50") != 0);
		BOOST_CHECK(em.category.compare("abstract") == 0);
		em = search.find("幻");
		BOOST_CHECK(em.checksums.sum("png", "px32").compare("743b2af6d489390821f0e56a5d357b50") == 0);
		BOOST_CHECK(em.copyright_lock == true);
		unsigned int i;
		for (i = 0; i < em.variants.size(); i++)
			if (em.variants[i].compare("幻(白)") == 0)
				break;
		BOOST_CHECK(em.variants[i].compare("幻(白)") == 0);
		BOOST_CHECK(em.user_id.compare("Zero") == 0);
	}

	BOOST_AUTO_TEST_CASE(search_term) {
		// Empty search provides empty results
		//BOOST_CHECK(search.term("").emoji.size() == 0);
		Emojidex::Data::Collection term = search.term("pudding");
		BOOST_CHECK(term.opts.getPage() == 1);
		BOOST_CHECK(term.emoji.size() > 0);
		//BOOST_CHECK(Emojidex::escapeCode("cry(pudding)").compare("cry\\(pudding\\)") == 0);
		term = search.term("cry%28pudding%29");
		BOOST_CHECK(term.opts.getPage() == 1);
		BOOST_CHECK(term.emoji.size() > 0);
		term = search.term("(プリン)");
		BOOST_CHECK(term.opts.getPage() == 1);
		BOOST_CHECK(term.emoji.size() > 0);

	}

	BOOST_AUTO_TEST_CASE(search_tags) {
		std::vector<std::string> test_tag(1);
		test_tag[0] = "linux";
		Emojidex::Data::Collection tags = search.tags(test_tag);
		BOOST_CHECK(tags.opts.getPage() == 1);
		BOOST_CHECK(tags.emoji.size() > 0);

		std::vector<std::string> test_tags{"linux", "OSS"};
		tags = search.tags(test_tags);
		BOOST_CHECK(tags.opts.getPage() == 1);
		BOOST_CHECK(tags.emoji.size() > 0);
	}

	BOOST_AUTO_TEST_CASE(search_advanced) {
		std::vector<std::string> test_tags = {"linux", "OSS"};
		std::vector<std::string> test_categories = {"symbols"};

		Emojidex::Data::Collection advanced = search.advanced("ux", test_categories, test_tags);
		BOOST_CHECK(advanced.opts.getPage() == 1);
		BOOST_CHECK(advanced.emoji.size() > 0);
	}
BOOST_AUTO_TEST_SUITE_END()

///////////////////////////////////////////////////////////////////////////////
// User tests
///////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(service_user_suite)
	Emojidex::Service::User user;

	// User does not yet have status
	BOOST_AUTO_TEST_CASE(user_uninitialized) {
		BOOST_TEST_MESSAGE("User initialize");
		BOOST_CHECK(user.status == Emojidex::Service::User::AuthStatusCode::NONE);
		BOOST_CHECK(user.username.compare("") == 0);
		BOOST_CHECK(user.pro == false);
		BOOST_CHECK(user.premium == false);
		BOOST_CHECK(user.history_total == 0);
		BOOST_CHECK(user.history_page == 0);
		BOOST_CHECK(user.history.size() == 0);
		BOOST_CHECK(user.favorites.emoji.size() == 0);
	}

	// User authentication by token
	BOOST_AUTO_TEST_CASE(user_auth) {
		BOOST_TEST_MESSAGE("User authorize");
		// NOTE: these are the "test" user credentials. This is an actual account.
		// If anyone else is running specs at the same time they will be using this 
		// account. Therefore it can be expected some specs may fail when run simultaniously.
		
		// Test a failure first
		BOOST_CHECK_EQUAL(user.authorize("test", "12345"), false);
		BOOST_CHECK_EQUAL(user.status, Emojidex::Service::User::AuthStatusCode::UNVERIFIED);

		// This should succeed
		BOOST_CHECK_EQUAL(user.authorize("test", 
			"1798909355d57c9a93e3b82d275594e7c7c000db05021138"), true);
		BOOST_CHECK_EQUAL(user.status, Emojidex::Service::User::AuthStatusCode::VERIFIED);
		BOOST_CHECK(user.username.compare("test") == 0);

	}

	// User favorites
	BOOST_AUTO_TEST_CASE(user_favorites) {
		BOOST_TEST_MESSAGE("User favorites");
		user.authorize("test", "1798909355d57c9a93e3b82d275594e7c7c000db05021138");

		BOOST_CHECK(user.syncFavorites());
		// Just in case
		BOOST_CHECK(user.addFavorite("drift"));
		unsigned int num_favorites = user.favorites.emoji.size();
		BOOST_CHECK(num_favorites > 0);
		BOOST_CHECK(user.removeFavorite("drift"));
		//One favorite should have been removed
		BOOST_CHECK(user.favorites.emoji.size() == num_favorites - 1);
		//Try removing again
		num_favorites = user.favorites.emoji.size();
		//Favorite should already be gone
		BOOST_CHECK(user.removeFavorite("drift") == false);
		//No more emoji should have been removed (emoji was already removed)
		BOOST_CHECK(user.favorites.emoji.size() == num_favorites);
	}

	// User history
	BOOST_AUTO_TEST_CASE(user_history) {
		BOOST_TEST_MESSAGE("User history");
		user.authorize("test", "1798909355d57c9a93e3b82d275594e7c7c000db05021138");

		user.syncHistory(0, 2);
		BOOST_CHECK(user.history.size() > 0);
		BOOST_CHECK(user.history_total > 0);
		BOOST_CHECK(user.history_page == 1);
		unsigned int size_mark = user.history.size();
		BOOST_TEST_MESSAGE("Size of history at first sync (limit 2): " << size_mark);
		std::vector<Emojidex::Service::HistoryItem> hist_page = user.syncHistory(2, 100);
		BOOST_TEST_MESSAGE("User history is limited to max 50 items for normal users, got: " << hist_page.size());
		BOOST_CHECK(hist_page.size() == 50);

		BOOST_CHECK(user.history.size() > size_mark);
		BOOST_CHECK(user.addHistory("poop") == true);
		BOOST_CHECK(user.history[0].emoji_code.compare("poop") == 0);

		BOOST_CHECK(user.addHistory("cry(pudding)") == true);
		BOOST_CHECK(user.history[0].emoji_code.compare("cry(pudding)") == 0);

		BOOST_CHECK(user.addHistory("cry%28wh%29") == true);
		BOOST_CHECK(user.history[0].emoji_code.compare("cry(wh)") == 0);

		BOOST_CHECK(user.addHistory("あきれ顔(黄)") == true);
		BOOST_CHECK(user.history[0].emoji_code.compare("あきれ顔(黄)") == 0);

		BOOST_TEST_MESSAGE("User history is sorted on sync");
		Emojidex::Service::HistoryItem hi = user.history[0];
		user.history[0] = user.history[1];
		user.history[1] = hi;
		hi = user.history[2];
		user.history[2] = user.history[3];
		user.history[3] = hi;
		BOOST_CHECK(user.history[0].last_used_posix < user.history[1].last_used_posix);
		BOOST_CHECK(user.history[1].last_used_posix > user.history[2].last_used_posix);
		BOOST_CHECK(user.history[2].last_used_posix < user.history[3].last_used_posix);

		user.syncHistory();
		BOOST_CHECK(user.history[0].last_used_posix > user.history[1].last_used_posix);
		BOOST_CHECK(user.history[1].last_used_posix > user.history[2].last_used_posix);
		BOOST_CHECK(user.history[2].last_used_posix > user.history[3].last_used_posix);
	}

	// User following (followers is tested by hand on a premium account)
	BOOST_AUTO_TEST_CASE(user_following) {
		BOOST_TEST_MESSAGE("User following");
		user.authorize("test", "1798909355d57c9a93e3b82d275594e7c7c000db05021138");

		user.addFollowing("emojidex");
		user.syncFollowing();
		BOOST_CHECK(user.following.size() > 0);
		unsigned int num_following = user.following.size();
		BOOST_TEST_MESSAGE("User following on sync: " << num_following);
		
		user.removeFollowing("emojidex");
		BOOST_TEST_MESSAGE("User following after remove: " << user.following.size());
		BOOST_CHECK(user.following.size() == num_following - 1);
		
		user.addFollowing("emojidex");
		BOOST_TEST_MESSAGE("User following after add: " << user.following.size());
		BOOST_CHECK(user.following.size() == num_following);
	}

BOOST_AUTO_TEST_SUITE_END()

///////////////////////////////////////////////////////////////////////////////
// Client tests
///////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(client_suite)
	// Check that this client is for version 1 of the api
	BOOST_AUTO_TEST_CASE(api_version) {
		BOOST_TEST_MESSAGE("API version");
		Emojidex::Client *client = new Emojidex::Client();
		BOOST_CHECK_EQUAL(client->apiVersion(), 1);
	}
BOOST_AUTO_TEST_SUITE_END()
