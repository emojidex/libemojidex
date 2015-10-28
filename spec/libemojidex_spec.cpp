#include <client.h>
#include <service/settings.h>
#include <service/transactor.h>

using namespace std;

#define BOOST_TEST_DYN_LINK 
#define BOOST_TEST_MODULE emojidex_test
#include <boost/test/unit_test.hpp>

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
		BOOST_TEST_MESSAGE("Checking raw GET:");
		BOOST_CHECK_NE(transactor.get("popular").compare(""), 0);
	}

	BOOST_AUTO_TEST_CASE(transactor_get_w_query_map) {
		BOOST_TEST_MESSAGE("Checking raw GET with a query map");
		std::unordered_map<string, string> q;
		q["detailed"] = "true";
		q["page"] = "2";
		BOOST_CHECK_NE(transactor.get("popular", q).compare(""), 0);
	}

	BOOST_AUTO_TEST_CASE(transactor_get_hash_query) {
		BOOST_TEST_MESSAGE("Checking raw GET with an instance query map");
		BOOST_CHECK_NE(transactor.get("popular", {{"detailed", "true"}, {"page", "3"}}).compare(""), 0);
	}

	BOOST_AUTO_TEST_CASE(transactor_get_static_point) {
		BOOST_TEST_MESSAGE("Checking raw GET against a static endpoint");
		BOOST_CHECK_NE(transactor.get("moji_codes").compare(""), 0);
		BOOST_CHECK_NE(transactor.get("moji_codes", {{"locale", "ja"}}).compare(""), 0);
	}

BOOST_AUTO_TEST_SUITE_END()

///////////////////////////////////////////////////////////////////////////////
// Index tests
///////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(service_indexes_suite)

	Emojidex::Service::Indexes idx;

	BOOST_AUTO_TEST_CASE(moji_codes_seed) {
		BOOST_CHECK(idx.mojiCodes().locale.compare("en") == 0);
		BOOST_CHECK_GT(idx.mojiCodes().moji_array.size(), 0);
		BOOST_CHECK_GT(idx.mojiCodes().moji_index.size(), 0);
		BOOST_CHECK(idx.mojiCodes().moji_index["🍕"].compare("pizza") == 0);
		BOOST_CHECK(idx.mojiCodes("ja").locale.compare("ja") == 0);
	}

	BOOST_AUTO_TEST_CASE(moji_codes_seed_ja) {
		BOOST_CHECK(idx.mojiCodes("ja").locale.compare("ja") == 0);
		BOOST_CHECK_GT(idx.mojiCodes().moji_array.size(), 0);
		BOOST_CHECK_GT(idx.mojiCodes().moji_index.size(), 0);
		BOOST_CHECK(idx.mojiCodes().moji_index["🌢"].compare("雫") == 0);
	}

	BOOST_AUTO_TEST_CASE(utf_emoji_seed) {
		Emojidex::Data::Collection utf = idx.utfEmoji("ja");
		BOOST_CHECK(utf.locale.compare("ja") == 0);
		BOOST_CHECK_GT(utf.emoji.size(), 0);
		BOOST_CHECK(utf.emoji["雫"].moji.compare("🌢") == 0);
	}

	BOOST_AUTO_TEST_CASE(extended_emoji_seed) {
		Emojidex::Data::Collection ext = idx.extendedEmoji();
		BOOST_CHECK(ext.locale.compare("en") == 0);
		BOOST_CHECK_GT(ext.emoji.size(), 0);
		BOOST_CHECK(ext.emoji["ninja"].category.compare("people") == 0);
	}

	BOOST_AUTO_TEST_CASE(emoji_index) {
		Emojidex::Data::Collection emoji = idx.emoji();
		int sz = emoji.emoji.size();
		BOOST_CHECK_GT(sz, 0);
		BOOST_CHECK_GT(emoji.total_count, sz);
		BOOST_CHECK_GT(emoji.more().emoji.size(), 0);
		BOOST_CHECK_GT(emoji.emoji.size(), sz);
	}

	BOOST_AUTO_TEST_CASE(emoji_index_detailed) {
		Emojidex::Data::Collection emoji = idx.emoji(1, 20, true);
		int sz = emoji.emoji.size();
		BOOST_CHECK(sz == 20);
		BOOST_CHECK_GT(emoji.more().emoji.size(), 0);
		BOOST_CHECK_EQUAL(emoji.emoji.size(), 40);
		BOOST_CHECK(emoji.emoji.begin()->second.checksums.svg.compare("") != 0);
		BOOST_CHECK(emoji.emoji.begin()->second.checksums.png["xhdpi"].compare("") != 0);
	}

	BOOST_AUTO_TEST_CASE(newest_index) {
		Emojidex::Data::Collection newest = idx.newest();
		int sz = newest.emoji.size();
		BOOST_CHECK_GT(sz, 0);
		BOOST_CHECK_GT(newest.more().emoji.size(), 0);
		BOOST_CHECK_GT(newest.emoji.size(), sz);
	}

	BOOST_AUTO_TEST_CASE(popular_index) {
		Emojidex::Data::Collection popular = idx.popular();
		int sz = popular.emoji.size();
		BOOST_CHECK_GT(sz, 0);
		BOOST_CHECK_GT(popular.more().emoji.size(), 0);
		BOOST_CHECK_GT(popular.emoji.size(), sz);
	}

BOOST_AUTO_TEST_SUITE_END()

///////////////////////////////////////////////////////////////////////////////
// Search tests
///////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(service_search_suite)

	Emojidex::Service::Search search;

	// Empty search provides empty results
	//BOOST_AUTO_TEST_CASE(term) {
		//BOOST_CHECK_GT(search.term("tears").size(), 0);
	//}

BOOST_AUTO_TEST_SUITE_END()

///////////////////////////////////////////////////////////////////////////////
// User tests
///////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(service_user_suite)

	Emojidex::Service::User user;

	// User does not yet have status
	BOOST_AUTO_TEST_CASE(user_uninitialized) {
		BOOST_CHECK(user.status == Emojidex::Service::User::AuthStatusCode::NONE);
		BOOST_CHECK(user.username.compare("") == 0);
		BOOST_CHECK(user.pro == false);
		BOOST_CHECK(user.premium == false);
		BOOST_CHECK(user.history.emoji.size() == 0);
		BOOST_CHECK(user.favorites.emoji.size() == 0);
	}

	// User authentication by token
	BOOST_AUTO_TEST_CASE(user_auth) {
		// NOTE: these are the "test" user credentials. This is an actual account.
		// If anyone else is running specs at the same time they will be using this 
		// account. Therefore it can be expected some specs may fail when run simultaniously.
		
		// Test a failure first
		BOOST_CHECK_EQUAL(user.authorize("test", "12345"), false);
		BOOST_CHECK_EQUAL(user.status, Emojidex::Service::User::AuthStatusCode::UNVERIFIED);
		BOOST_TEST_MESSAGE("RESPONSE IS: " << user.response);

		// This should succeed
		BOOST_CHECK_EQUAL(user.authorize("test", 
			"1798909355d57c9a93e3b82d275594e7c7c000db05021138"), true);
		BOOST_CHECK_EQUAL(user.status, Emojidex::Service::User::AuthStatusCode::VERIFIED);
		BOOST_CHECK(user.username.compare("test") == 0);

	}

	// User favorites
	BOOST_AUTO_TEST_CASE(user_favorites) {
		//user.authorize("test", "1798909355d57c9a93e3b82d275594e7c7c000db05021138");

		//user.syncFavorites();
		// Just in case
		//user.addFavorite("drift");
		//BOOST_CHECK(user.favorites.emoji.size() > 0);
		//TODO
	}

	// User history
	BOOST_AUTO_TEST_CASE(user_history) {
	//	user.authorize("test", "1798909355d57c9a93e3b82d275594e7c7c000db05021138");

	//	user.syncHistory();
	//	BOOST_CHECK(user.history.emoji.size() > 0);
	//	//TODO
	}

BOOST_AUTO_TEST_SUITE_END()

///////////////////////////////////////////////////////////////////////////////
// Client tests
///////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(client_suite)

	// Check that this client is for version 1 of the api
	BOOST_AUTO_TEST_CASE(api_version) {
		Emojidex::Client *client = new Emojidex::Client();
		BOOST_CHECK_EQUAL(client->apiVersion(), 1);
	}

BOOST_AUTO_TEST_SUITE_END()
