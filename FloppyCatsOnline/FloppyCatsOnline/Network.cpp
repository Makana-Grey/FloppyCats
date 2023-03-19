#include "Game.hpp"
#include "Network.hpp"
#include "Menu.hpp"
#include <fstream>
#include "path.hpp"
#include "definitions.hpp"
#include <IPv4resolver.hpp>

#include "features.hpp"

void Network::resolveSelfPoint() {
	const auto stuns = combine_paths(
		combine_paths(get_current_path(), DATA_FOLDER),
		STUNS_LIST_FILE
	);

	std::ifstream stream(stuns);
	std::string stun;

	unsigned short port = 3478;
	Packet req;
	auto req_id = getStunRequest(req);

	IpAddress sender;
	unsigned short sender_port = 0;
	Packet resp;

	SocketSelector selector;
	selector.add(socket_);

	if (stream.is_open()) {
		while (stream.good()) {
			stream >> stun;
			std::string cc = stun;
			stun = resolveIPv4(stun, "");

			if (stun != "") {
				if (socket_.send(req, stun, port) == Socket::Done) {
					if (selector.wait(seconds(WAIT_FOR_STUN_RESP_S))) {
						socket_.receive(resp, sender, sender_port);

						if (resolveStunResponse(resp, req_id, self_ip_, self_port_)) {
							break;
						}
					}
				}
			}
		}
	}

	selector.clear();
	stream.close();
}

Network::Network() {
	if (socket_.bind(Socket::AnyPort) != Socket::Done) {
		return;
	}

	resolveSelfPoint();
}

void Network::connect() {

}