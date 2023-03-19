#include "features.hpp"

constexpr uint16_t BINDING_REQUEST = 0x0001;
constexpr uint16_t BINDING_RESPONSE = 0x0101;
constexpr uint32_t MAGIC_COOKIE = 0x2112A442;
constexpr uint16_t MAPPED_ADDRES = 0x0001;
constexpr uint16_t XOR_MAPPED_ADDRES = 0x0020;
constexpr uint8_t IPV4 = 0x01;

std::array<uint8_t, 12> getStunRequest(sf::Packet& packet) {
	packet << BINDING_REQUEST;
	packet << (uint16_t)0x0000;
	packet << MAGIC_COOKIE;

	std::array<uint8_t, 12> transaction_id{};

	for (int i = 0; i < transaction_id.size(); i++)
	{
		transaction_id[i] = rand() % 256;
		packet << (uint8_t)(transaction_id[i]);
	}

	return transaction_id;
}

bool resolveStunResponse(sf::Packet& packet, std::array<uint8_t, 12> req_id, std::string& ip, uint16_t& port) {
	uint16_t resp = 0;
	packet >> resp;

	if (resp == BINDING_RESPONSE) {
		uint16_t msg_size = 0;
		packet >> msg_size;

		uint32_t mgk_cookie = 0;
		packet >> mgk_cookie;

		if (mgk_cookie == MAGIC_COOKIE) {
			std::array<uint8_t, 12> transaction_id{};

			for (int i = 0; i < transaction_id.size(); i++)
			{
				packet >> transaction_id[i];
				if (transaction_id[i] != req_id[i]) {
					return false;
				}
			}

			uint16_t counter = 0;
			uint16_t attribute_type = 0;
			while (counter < msg_size) {
				packet >> attribute_type;
				counter += 2;

				if (attribute_type == MAPPED_ADDRES) {
					uint16_t skip = 0;
					packet >> skip;
					counter += 2;

					uint8_t family = 0;
					packet >> family;
					packet >> family;
					counter += 2;

					if (family == IPV4) {
						packet >> port;

						uint8_t ip_part = 0;
						packet >> ip_part;
						ip = std::to_string(ip_part);
						for (unsigned i = 0; i < 3; i++) {
							packet >> ip_part;
							ip += "." + std::to_string(ip_part);
						}

						return true;
					}
					continue;
				}

				if (attribute_type == XOR_MAPPED_ADDRES) {
					uint16_t skip = 0;
					packet >> skip;
					counter += 2;

					uint8_t family = 0;
					packet >> family;
					packet >> family;
					counter += 2;

					if (family == IPV4) {
						packet >> port;
						port ^= 0x2112;

						uint8_t ip_part = 0;
						packet >> ip_part;
						ip_part ^= 0x21;
						ip = std::to_string(ip_part);

						packet >> ip_part;
						ip_part ^= 0x12;
						ip += "." + std::to_string(ip_part);

						packet >> ip_part;
						ip_part ^= 0xA4;
						ip += "." + std::to_string(ip_part);

						packet >> ip_part;
						ip_part ^= 0x42;
						ip += "." + std::to_string(ip_part);

						return true;
					}
					continue;
				}
			}
		}
	}

	return false;
}