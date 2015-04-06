#include <client.h>
#include <service/search.h>
#include <service/transactor.h>

#define BOOST_TEST_DYN_LINK 
#define BOOST_TEST_MODULE emojidex_test
#include <boost/test/unit_test.hpp>

///////////////////////////////////////////////////////////////////////////////
// Transactor tests
///////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(service_transactor_suite)

	// Check that defaults are accurate
	BOOST_AUTO_TEST_CASE(transactor_info_defaults) {
		Emojidex::Service::Transactor transactor;
		BOOST_CHECK_EQUAL(transactor.info.api_host, "www.emojidex.com");
		BOOST_CHECK_EQUAL(transactor.info.api_prefix, "/api/v1/");
		BOOST_CHECK_EQUAL(transactor.info.api_protocol, "https");
		BOOST_CHECK_EQUAL(transactor.info.cdn_host, "cdn.emojidex.com");
		BOOST_CHECK_EQUAL(transactor.info.cdn_prefix, "/emoji/");
		BOOST_CHECK_EQUAL(transactor.info.cdn_protocol, "http");
		BOOST_CHECK_EQUAL(transactor.info.closed_net, false);
	}

	BOOST_AUTO_TEST_CASE(transactor_get) {
		Emojidex::Service::Transactor transactor;
		BOOST_CHECK_NE(transactor.get("popular").compare(""), 0);

		unordered_map<string, string> q;
		q["detailed"] = "true";
		q["page"] = "2";
		BOOST_CHECK_NE(transactor.get("popular", q).compare(""), 0);

		BOOST_CHECK_NE(transactor.get("popular", {{"detailed", "true"}, {"page", "3"}}).compare(""), 0);
	}

BOOST_AUTO_TEST_SUITE_END()

///////////////////////////////////////////////////////////////////////////////
// Index tests
///////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(service_indexes_suite)

	Emojidex::Service::Indexes idx;

	BOOST_AUTO_TEST_CASE(moji_codes_seed) {
		BOOST_CHECK(idx.mojiCodes()->locale.compare("en") == 0);
		BOOST_CHECK_GT(idx.mojiCodes()->mojiArray.size(), 0);
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
// Client tests
///////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(client_suite)

	// Check that this client is for version 1 of the api
	BOOST_AUTO_TEST_CASE(api_version) {
		Emojidex::Client *client = new Emojidex::Client();
		BOOST_CHECK_EQUAL(client->apiVersion(), 1);
	}

BOOST_AUTO_TEST_SUITE_END()
