#pragma once
#include <SFML/Network.hpp>
#include <string>
#include <array>
#include <cstdint>
#include <winsock2.h>

std::array<uint8_t, 12> createStunRequest(sf::Packet& packet);

bool resolveStunResponse(sf::Packet& packet, std::array<uint8_t, 12> req_id, std::string& ip, uint16_t& port);

bool setHttpClientHost(sf::Http& http);

sf::Http::Request createHttpRequest(sf::Http::Request::Method method, std::string urn);

bool resolveHttpResponse(sf::Http& http, sf::Http::Request& req, const std::string body, std::string& resp_body);