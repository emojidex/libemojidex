#include <client.h>
#include <client/comm.h>

#define BOOST_TEST_DYN_LINK 
#define BOOST_TEST_MODULE emojidex_test
#include <boost/test/unit_test.hpp>

///////////////////////////////////////////////////////////////////////////////
// Raw Comm tests
///////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(comm_suite)

// Check that defaults are accurate
BOOST_AUTO_TEST_CASE(comm_info_defaults) {
	Emojidex::Comm *comm = new Emojidex::Comm();
	BOOST_CHECK_EQUAL(comm->info.api_url, "www.emojidex.com/api/v1/");
	BOOST_CHECK_EQUAL(comm->info.api_protocol, "https");
	BOOST_CHECK_EQUAL(comm->info.cdn_url, "cdn.emojidex.com/");
	BOOST_CHECK_EQUAL(comm->info.cdn_protocol, "http");
	BOOST_CHECK_EQUAL(comm->info.closed_net, false);
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

///////////////////////////////////////////////////////////////////////////////
// Search Client tests
///////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(search_client_suite)

Emojidex::SearchClient *searchClient = new Emojidex::SearchClient();

// Empty search provides empty results
BOOST_AUTO_TEST_CASE(term) {
	BOOST_CHECK_EQUAL(searchClient->term(""), "");
}

BOOST_AUTO_TEST_SUITE_END()
