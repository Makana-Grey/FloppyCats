#include "pch.h"
#include "includes/IPv4resolver.hpp"

const std::string resolveIPv4(const std::string hostname, const std::string port) {
	using namespace boost;
	using namespace boost::asio;
	using namespace boost::asio::ip;

	tcp::resolver::query query(
		hostname,
		port,
		tcp::resolver::query::numeric_service
	);
	io_service ios;
	tcp::resolver resolver(ios);
	system::error_code error_code;

	tcp::resolver::iterator iterator = resolver.resolve(query, error_code);

	if (error_code.value() != 0) {
		return "";
	}


	tcp::resolver::iterator end;
	while (++iterator != end) {
		tcp::endpoint endpoint = iterator->endpoint();
		if (endpoint.address().is_v4()) {
			return endpoint.address().to_string();
		}
	}

	return "";
}