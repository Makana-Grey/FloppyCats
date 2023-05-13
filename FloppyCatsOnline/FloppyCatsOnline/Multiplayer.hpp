#include "Scene.hpp"
#include "Network.hpp"
#include "Lobby.hpp"
#include <SFML/Graphics.hpp>

#ifndef _multiplayer_hpp
#define _multiplayer_hpp

class Multiplayer : public Scene {
private:
	Network network_;
	Lobby lobby_;
public:
	Multiplayer();
	virtual void update() override;
	virtual void fixedUpdate() override;
};

#endif // !_multiplayer_hpp