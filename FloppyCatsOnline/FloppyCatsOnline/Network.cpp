#include "Game.hpp"
#include "Network.hpp"
#include "Menu.hpp"
#include <fstream>
#include "path.hpp"
#include "definitions.hpp"
#include <IPv4resolver.hpp>
#include <format>
#include <json/json.h>

#include "features_client.hpp"

Network::Network() {}

bool Network::initialize() {
	if (socket_.bind(Socket::AnyPort) != Socket::Done) {
		return false;
	}
	if (!resolvePoint()) {
		return false;
	}
	if (!setHttpClientHost(http_)) {
		return false;
	}

	return true;
}

bool Network::resolvePoint() {
	bool result = false;

	const auto stuns = combine_paths(
		combine_paths(get_current_path(), DATA_FOLDER),
		STUNS_LIST_FILE
	);

	std::ifstream stream(stuns);
	std::string stun;

	unsigned short port = 3478;
	Packet req;
	auto req_id = createStunRequest(req);

	IpAddress sender;
	unsigned short sender_port = 0;
	Packet resp;

	SocketSelector selector;
	selector.add(socket_);

	try {
		if (stream.is_open()) {
			while (stream.good()) {
				stream >> stun;
				std::string cc = stun;
				stun = resolveIPv4(stun, "");

				if (stun != "") {
					if (socket_.send(req, stun, port) == Socket::Done) {
						if (selector.wait(seconds(WAIT_FOR_STUN_RESP_S))) {
							socket_.receive(resp, sender, sender_port);

							if (resolveStunResponse(resp, req_id, ip_, port_)) {
								result = true;
								break;
							}
						}
					}
				}
			}
		}
	}
	catch (...) {}

	selector.clear();
	stream.close();

	return result;
}

bool Network::connect() {
	Http::Request request = createHttpRequest(Http::Request::Post, API_CONNECTION_CONNECT);
	std::string_view jsonTemplate = R"({{ "ip": "{}", "port": {} }})";
	std::string body = std::vformat(jsonTemplate, std::make_format_args(ip_, port_));
	std::string resp_body = "";

	if (resolveHttpResponse(http_, request, body, resp_body)) {
		Json::Value root;
		Json::Reader reader;

		if (reader.parse(resp_body, root)) {
			name = root.get("name", "").asString();
			token_ = root.get("token", "").asString();
			return true;
		}
	}

	return false;
}

bool Network::refresh() {
	Http::Request request = createHttpRequest(Http::Request::Post, API_CONNECTION_REFRESH);
	
	std::string_view jsonTemplate = R"({{ "ip": "{}", "port": {}, "token": "{}" }})";
	std::string body = std::vformat(jsonTemplate, std::make_format_args(ip_, port_, token_));

	std::string resp_body = "";

	return resolveHttpResponse(http_, request, body, resp_body);
}

bool Network::all(std::vector<std::string>& players) {
	Http::Request request = createHttpRequest(Http::Request::Get, API_PLAYERS_ALL);
	std::string resp_body = "";

	if (resolveHttpResponse(http_, request, "", resp_body)) {
		Json::Value root;
		Json::Reader reader;

		if (reader.parse(resp_body, root)) {
			unsigned size = root.size();
			for (unsigned i = 0; i < size; i++) {
				players.push_back(root[i].asString());
			}
			return true;
		}
	}

	return false;
}

bool Network::search(const std::string query, std::string& name) {
	Http::Request request = createHttpRequest(Http::Request::Post, API_PLAYERS_SEARCH);
	std::string_view jsonTemplate = R"({{ "query": "{}" }})";
	std::string body = std::vformat(jsonTemplate, std::make_format_args(query));
	std::string resp_body = "";

	if (resolveHttpResponse(http_, request, body, resp_body)) {
		name = resp_body;
		return true;
	}

	return false;
}

bool Network::point(const std::string name, std::string& ip, uint16_t& port) {
	Http::Request request = createHttpRequest(Http::Request::Post, API_PLAYERS_POINT);
	std::string_view jsonTemplate = R"({{ "name": "{}" }})";
	std::string body = std::vformat(jsonTemplate, std::make_format_args(name));
	std::string resp_body = "";

	if (resolveHttpResponse(http_, request, body, resp_body)) {
		Json::Value root;
		Json::Reader reader;

		if (reader.parse(resp_body, root)) {
			ip = root.get("ip", "").asString();
			port = root.get("port", "").asUInt();
			return true;
		}
	}

	return false;
}

bool Network::setPlay(const bool value) {
	Http::Request request = createHttpRequest(Http::Request::Put, API_PLAYER_PLAY);

	std::string_view jsonTemplate = R"({{ "isPlay": {}, "token": "{}" }})";
	std::string body = std::vformat(jsonTemplate, std::make_format_args(value, token_));

	std::string resp_body = "";

	return resolveHttpResponse(http_, request, body, resp_body);
}

bool Network::setPublic(const bool value) {
	Http::Request request = createHttpRequest(Http::Request::Put, API_PLAYER_PUBLIC);

	std::string_view jsonTemplate = R"({{ "isPublic": {}, "token": "{}" }})";
	std::string body = std::vformat(jsonTemplate, std::make_format_args(value, token_));

	std::string resp_body = "";

	return resolveHttpResponse(http_, request, body, resp_body);
}