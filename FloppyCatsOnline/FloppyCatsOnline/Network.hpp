#include <string>
#include <SFML/Network.hpp>
#include <cstdint>

#ifndef _network_hpp
#define _network_hpp

class Network {
private:
	UdpSocket socket_;
	std::string self_ip_ = "";
	uint16_t self_port_ = 0;

	void resolveSelfPoint();
public:
	Network();

	bool isConnect = false;
	bool isConnecting = false;

	void connect();
};


#endif // !_network_hpp
