#pragma once
#include <SFML/Network.hpp>
#include <string>
#include <array>
#include <cstdint>
#include <winsock2.h>

std::array<uint8_t, 12> getStunRequest(sf::Packet& packet);

bool resolveStunResponse(sf::Packet& packet, std::array<uint8_t, 12> req_id, std::string& ip, uint16_t& port);