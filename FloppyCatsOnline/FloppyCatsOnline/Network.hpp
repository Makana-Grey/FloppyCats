#include <string>
#include <SFML/Network.hpp>
#include <cstdint>
#include <vector>

#ifndef _network_hpp
#define _network_hpp

class Network {
private:
	UdpSocket socket_;
	std::string ip_ = "";
	uint16_t port_ = 0;

	Http http_;

	std::string token_ = "";

public:
	std::string name = "";

	Network();
	bool initialize();
	bool resolvePoint();

	bool connect();
	bool refresh();

	bool all(std::vector<std::string>& players);
	bool search(const std::string query, std::string& name);
	bool point(const std::string name, std::string& ip, uint16_t& port);

	bool setPlay(const bool value);
	bool setPublic(const bool value);
};


#endif // !_network_hpp
