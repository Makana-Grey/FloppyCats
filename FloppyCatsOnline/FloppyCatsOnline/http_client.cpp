#include "features_client.hpp"
#include "definitions.hpp"
#include <string>

bool setHttpClientHost(sf::Http& http) {
#if MODE == DEPLOY
#ifdef NDEBUG
	http.setHost(API_PROD);
	return true;
#endif
#else 
	http.setHost(API_URL, API_PORT);
	return true;
#endif
}

sf::Http::Request createHttpRequest(sf::Http::Request::Method method, std::string urn) {
	sf::Http::Request request;
	request.setMethod(method);
	request.setUri(urn);
	request.setField("Accept", "*/*");
	request.setField("Content-type", "application/json; charset=utf-8");
	request.setHttpVersion(1, 1);

	return request;
}

bool resolveHttpResponse(sf::Http& http, sf::Http::Request& req, const std::string body, std::string& resp_body) {
	req.setBody(body);
	sf::Http::Response response = http.sendRequest(req);

	if (response.getStatus() == 200) {
		resp_body = response.getBody();

		return true;
	}

	return false;
}