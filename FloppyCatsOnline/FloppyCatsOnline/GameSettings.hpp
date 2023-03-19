#include "Scene.hpp"
#include <SFML/Graphics.hpp>

#ifndef _game_settings_hpp
#define _game_settings_hpp

class GameSettings : public Scene {
private:
public:
	GameSettings();
	virtual void update() override;
	virtual void fixedUpdate() override;
};

#endif // !_game_settings_hpp